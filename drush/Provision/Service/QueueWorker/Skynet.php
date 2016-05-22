<?php

/**
 * The Skynet implementation of the QueueWorker service type.
 */
class Provision_Service_QueueWorker_Skynet extends Provision_Service_QueueWorker {

  /**
   * The default value for the restart command input.
   */
  function default_restart_cmd() {
    return "/usr/bin/supervisorctl restart skynet-queue";
  }


  /**
   * Initialize this class, including option handling.
   */
  function init_server() {
    parent::init_server();

    /**
     * Register configuration classes for the create_config / delete_config methods.
     */
    $this->configs['server'][] = 'Provision_Config_QueueWorker';

    /**
     * Save configurable values in the server context.
     */
    $this->server->setProperty('heartbeat_interval', '60');
    $this->server->setProperty('concurrent_tasks', '1');

    /**
     * Save non-configurable values in the server context.
     */
    $this->server->skynet_config_path = $this->server->config_path . '/skynet';
  }


  /**
   * Pass additional values to the config file templates.
   */
  function config_data($config = null, $class = null) {
    $data = parent::config_data($config, $class);

    /**
     * Pass database credentials to config files.
     */
    // TODO: confirm that we're getting @hostmaster's creds.
    $site_context = drush_get_context('site');
    $data['db_host'] = $site_context['db_host'];
    $data['db_port'] = $site_context['db_port'];
    $data['db_name'] = $site_context['db_name'];
    $data['db_user'] = $site_context['db_user'];
    $data['db_passwd'] = $site_context['db_passwd'];

    return $data;
  }

  /**
   * Implementation of service verify.
   */
  function verify() {
    parent::verify();
    if ($this->context->type == 'server') {
      // Create the configuration file directory.
      provision_file()->create_dir($this->server->skynet_config_path, dt("Skynet configuration"), 0700);
      // Sync the directory to the remote server if needed.
      $this->sync($this->server->skynet_config_path); // needed? maybe later.
    }
  }
}
