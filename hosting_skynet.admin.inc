<?php
/**
 * @file
 * Configuration forms for the Skynet queue daemon.
 */

/**
 * Configuration form for Skynet queue daemon.
 */
function hosting_skynet_settings_form($form, &$form_state) {

  $form['description'] = array(
    '#type' => 'markup',
    '#value' => t('Note that saving this form will trigger a verify task for the hostmaster site. This is required in oder to write updated settings to the config file for the Python daemon.'),
    '#weight' => -100,
  );

#  $form['hosting_skynet_polling_frequency'] = array();
#  $form['hosting_skynet_check_interval'] = array();
  return system_settings_form($form);
}

/**
 * Implements hook_form_alter().
 */
function hosting_skynet_form_alter(&$form, &$form_state, $form_id) {
  $form['#submit'][] = 'hosting_skynet_settings_form_submit';
}

/**
 * Submit callback for hosting_skynet_settings_form().
 */
function hosting_skynet_settings_form_submit($form, &$form_state) {
  if ($nid = hosting_get_hostmaster_site_nid()) {
    drupal_set_message(t('Added verify task for Hostmaster site, in order to update skynet configuration files.'));
    hosting_add_task($nid, 'verify');
  }
  else {
    drupal_set_message(t('Failed to add verify task for Hostmaster site. Skynet configuration files will not be updated.'), 'error');
  }
}

