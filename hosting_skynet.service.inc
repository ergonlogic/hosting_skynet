<?php

/**
 * @file
 * Skynet task queue service implementation for the hosting front end.
 */

/**
 * The base service type class, registered with hook_hosting_service_type.
 */
class hostingService_QueueWorker extends hostingService {
  public $service = 'QueueWorker';
}


/**
 * An implementation of the queue worker service type, registered with hook_hosting_service.
 */
class hostingService_QueueWorker_Skynet extends hostingService_QueueWorker {

  public $type = 'Skynet';

  public $has_port = FALSE;

  public $has_restart_cmd = TRUE;

  protected $heartbeat_interval = 60;
  
  protected $concurrent_tasks = 1;

  function default_restart_cmd() {
    return "/usr/bin/supervisorctl restart skynet-queue";
  }

  /**
   * node operations
   */

  /**
   * Load associated values for the service.
   */
  function load() {
    parent::load();
    $this->heartbeat_interval = variable_get('hosting_skynet_heartbeat_interval_' . $this->server->nid, $this->heartbeat_interval);
    $this->concurrent_tasks = variable_get('hosting_skynet_concurrent_tasks_' . $this->server->nid, $this->concurrent_tasks);
  }

  /**
   * Display settings on the server node page.
   *
   * @param
   *   A reference to the associative array of the subsection of the page
   *   reserved for this service implementation.
   */
  function view(&$render) {
    parent::view($render);
    $render['heartbeat_interval'] = array(
      '#type' => 'item',
      '#title' => t('Heartbeat interval'),
      '#markup' => filter_xss($this->heartbeat_interval),
    );
    $render['concurrent_tasks'] = array(
      '#type' => 'item',
      '#title' => t('Parallel tasks'),
      '#markup' => filter_xss($this->concurrent_tasks),
    );
  }

  /**
   * Extend the server node form.
   *
   * Modify the reference passed to the method to add additional implementation
   * specific fields to be stored and managed.
   *
   * @param
   *   A reference to the associative array of the subsection of the form
   *   reserved for this service implementation.
   */
  function form(&$form) {
    parent::form($form);

    $form['heartbeat_interval'] = array(
      '#type' => 'textfield',
      '#title' => t('Heartbeat interval'),
      '#description' => t('The number of seconds that can pass before a task queue is considered down.'),
      '#default_value' => $this->heartbeat_interval,
    );

    $form['concurrent_tasks'] = array(
      '#type' => 'textfield',
      '#title' => t('Parallel tasks'),
      '#description' => t('The maximum number of tasks to process in parallel.'),
      '#default_value' => $this->concurrent_tasks,
    );

  }

  /**
   * Validate a form submission.
   */
  function validate(&$node, &$form, &$form_state) {
    parent::validate($node, $form, $form_state);

    if ($this->heartbeat_interval < 30) {
      form_set_error('heartbeat_interval', t("The heartbeat interval must not be shorter than 30 seconds."));
    }
    if ($this->concurrent_tasks < 1) {
      form_set_error('concurrent_tasks', t("Cannot run fewer than one (1) task at a time."));
    }
  }

  /**
   * Insert a record into the database.
   *
   * Called by hosting_server_hook_insert().
   *
   * The values associated with this implementation have already
   * been set as properties of $this object, so we now need to
   * save them.
   */
  function insert() {
    parent::insert();
    variable_set('hosting_skynet_heartbeat_interval_' . $this->server->nid, $this->heartbeat_interval);
    variable_set('hosting_skynet_concurrent_tasks_' . $this->server->nid, $this->concurrent_tasks);
  }

  /**
   * Update a record in the database.
   *
   * Called by hosting_server_hook_update().
   */
  function update() {
    parent::update();
    variable_set('hosting_skynet_heartbeat_interval_' . $this->server->nid, $this->heartbeat_interval);
    variable_set('hosting_skynet_concurrent_tasks_' . $this->server->nid, $this->concurrent_tasks);
  }

  /**
   * Delete a record from the database, based on server node.
   */
  function delete() {
    parent::delete();
    variable_del('hosting_skynet_heartbeat_interval_' . $this->server->nid);
    variable_del('hosting_skynet_concurrent_tasks_' . $this->server->nid);
  }

  /**
   * Delete a specific revision from the database.
   */
  function delete_revision() {
    parent::delete_revision();
  }

  /**
   * Pass values to the provision backend when we call provision-save.
   */
  public function context_options($task_type, $ref_type, &$task) {
    parent::context_options($task_type, $ref_type, $task);

    $task->context_options['heartbeat_interval'] = $this->heartbeat_interval;
    $task->context_options['concurrent_tasks'] = $this->concurrent_tasks;
  }
}

