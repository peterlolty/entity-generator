<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */

/**
 * Class model_modelentity_handler_edit_link_field
 */
class model_modelentity_handler_edit_link_field extends model_modelentity_handler_link_field {
  /**
   * Constructor.
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  /**
   * Render link.
   *
   * @param array $values
   *   Values.
   *
   * @return string
   *   Link.
   */
  public function render($values) {
    $type = $values->{$this->aliases['type']};

    // Creating a dummy model_modelentity to check access against.
    /*$dummy_model_modelentity = (object) array('type' => $type);
    if (!model_modelentity_access('edit', $dummy_model_modelentity)) {
      return;
    }*/

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $model_modelentity_id = $values->{$this->aliases['model_modelentity_id']};

    return l($text, 'model/modelentities/' . $model_modelentity_id . '/edit');
  }
}
