<?php
/**
 * @file
 * The hosting feature definition for the Skynet queue daemon.
 */

/**
 * Implements hook_hosting_feature().
 */
function hosting_skynet_hosting_feature() {
  $features['skynet'] = array(
    'title' => t('Skynet queue daemon'),
    'description' => t('Runs the Skynet tasks queue as a daemonized process.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_skynet',
    'group' => 'experimental',
  );
  return $features;
}
