<?php

/**
 * The Controller for Modelentity entities
 *
 * Class ModelentityController
 */
class ModelentityController extends EntityAPIController {
  /**
   * Constructor.
   *
   * @param string $entity_type
   *   Entity type.
   */
  public function __construct($entity_type) {
    parent::__construct($entity_type);
  }

  /**
   * Create a model_modelentity - we first set up the values that are specific
   * to our model_modelentity schema but then also go through the EntityAPIController
   * function.
   *
   * @param array $values
   *   The values of the model_modelentity.
   *
   * @return object
   *   A model_modelentity object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Modelentity.
    $values += array(
      'model_modelentity_id' => '',
      'uid'            => 0,
      'is_new'         => TRUE,
      'title'          => '',
      'created'        => '',
      'changed'        => '',
    );

    $model_modelentity = parent::create($values);

    return $model_modelentity;
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    global $user;
    if(isset($entity->is_new) && $entity->is_new){
      $entity->uid = $user->uid;
      $entity->created = REQUEST_TIME;
    }
    $entity->changed = REQUEST_TIME;
    parent::save($entity,$transaction);
  }

  /**
   * Overriding the buildContent function to add entity specific fields.
   *
   * @param object $entity
   *   Entity.
   * @param string $view_mode
   *   View mode.
   * @param string $langcode
   *   Language code.
   * @param array $content
   *   Content.
   *
   * @return array
   *   The content built.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);

    return $content;
  }
}
