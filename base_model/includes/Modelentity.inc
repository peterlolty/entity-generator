<?php

/**
 * The class used for model_modelentity entities
 *
 * Class Modelentity
 */
class Modelentity extends Entity {
  /**
   * Constructor.
   *
   * @param array $values
   *   Values.
   *
   * @throws \Exception
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'model_modelentity');
  }

  /**
   * Return model_modelentity label.
   *
   * @return string
   *   Label.
   */
  protected function defaultLabel() {
    return $this->name;
  }

  /**
   * Return model_modelentity URI.
   *
   * @return array
   *   Uri.
   */
  protected function defaultUri() {
    return array('path' => 'model/modelentities/' . $this->model_modelentity_id);
  }
}