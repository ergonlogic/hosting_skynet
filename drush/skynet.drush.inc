<?php
/**
 * @file Provides the Skynet Drush hooks.
 */

require_once(dirname(__FILE__) . '/includes/templates.inc');

/**
 * Implements drush_hook_post_COMMAND().
 *
 * Whenever we migrate the hostmaster site, we need to re-write the skynet
 * config file with the new DB credentials, and restart the service.
 */
function drush_skynet_post_provision_verify() {
  if (d()->type == 'site' && d()->profile == 'hostmaster') {
    _drush_skynet_create_config();
    _drush_skynet_restart_service();
  }
}

/**
 * Implements drush_HOOK_post_COMMAND().
 */
function drush_skynet_post_provision_migrate() {
  drush_skynet_post_provision_verify();
}

/**
 * Implements drush_HOOK_post_COMMAND().
 *
 * When we install the hostmaster site, we need to write the skynet config file
 * with the DB credentials, and start the service.
 */
function drush_skynet_post_provision_install() {
  if (d()->type == 'site' && d()->profile == 'hostmaster') {
    drush_skynet_post_provision_verify();
  }
}

/**
 * Helper function to write the skynet config file.
 */
function _drush_skynet_create_config() {
  $template_path = dirname(__FILE__) . '/templates/skynet.conf.tpl.php'; 
  $dest_path = '/var/aegir/config/skynet/skynet.conf';
  $site_context = drush_get_context('site');
  $variables = array(
    'host' => $site_context['db_host'],
    'db' => $site_context['db_name'], 
    'user' => $site_context['db_user'], 
    'passwd' => $site_context['db_passwd'],     
  );
  $mode = 0600;
  $overwrite = TRUE;
  skynet_template($template_path, $dest_path, $variables, $mode, $overwrite);
}

/**
 * Helper function to restart the skynet service.
 */
function _drush_skynet_restart_service() {
  if (drush_shell_exec('sudo supervisorctl restart skynet-queue')) {
    drush_log('Restarted Skynet queue service.');
  }
  else {
    drush_set_error('SKYNET_ERROR_RESTARTING_SERVICE', dt("An error occurred restarting the Skynet queue service. The command output follows:\n :output", array(':output' => drush_shell_exec_output())));
  }
}

/**
 * @file
 *  Declares a new service type and a basic implementation of it.
 *  It matches the same service definition in the hosting front end.
 */

/**
 * Implements hook_drush_init().
 */
function skynet_drush_init() {
  skynet_provision_register_autoload();
}

/**
 * Register our directory as a place to find provision classes.
 */
function skynet_provision_register_autoload() {
  static $loaded = FALSE;
  if (!$loaded) {
    $loaded = TRUE;
    provision_autoload_register_prefix('Provision_', dirname(__FILE__));
  }
}

/**
 * Expose the service type this extension defines to Provision.
 */
function skynet_provision_services() {
  skynet_provision_register_autoload();
  return array('TaskQueue' => 'Skynet');
}
