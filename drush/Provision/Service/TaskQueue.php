<?php

/**
 * The service type base class.
 *
 * All implementations of the service type will inherit this class.
 * This class should define the 'public API' to be used by the rest
 * of the system, which should not expose implementation details.
 */
class Provision_Service_TaskQueue extends Provision_Service {
  public $service = 'TaskQueue';

  /**
   * Called on provision-verify.
   *
   * We change what we will do based on what the 
   * type of object the command is being run against.
   */
  function verify() {
    $this->create_config(d()->type);
    $this->parse_configs();
  }

  /**
   * PUBLIC API!
   */

  /**
   * Commonly something like running the restart_cmd or sending SIGHUP to a process.
   */
  function parse_configs() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }

  /**
   * Generate a site specific configuration file
   */
  function create_site_config() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }

  /**
   * Remove an existing site configuration file.
   */
  function delete_site_config() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }

  /**
   * Add a new platform specific configuration file.
   */
  function create_platform_config() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }

  /**
   * Remove an existing platform configuration file.
   */
  function delete_platform_config() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }

  /**
   * Create a new server specific configuration file.
   */
  function create_server_config() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }

  /**
   * Remove an existing server specific configuration file
   */
  function delete_server_config() {
    // TODO: Evaluate whether this is still needed.
    return TRUE;
  }
}
