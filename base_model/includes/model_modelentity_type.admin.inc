<?php

/**
 * @file
 * Modelentity type editing UI.
 */

/**
 * UI controller.
 */
class ModelentityTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage ELabel entity types, including adding
		and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the model_modelentity type editing form.
 */
function model_modelentity_type_form($form, &$form_state, $model_modelentity_type, $op = 'edit') {

  if ($op == 'clone') {
    $model_modelentity_type->label .= ' (cloned)';
    $model_modelentity_type->type = '';
  }

  $form['label'] = array(
    '#title'         => t('Label'),
    '#type'          => 'textfield',
    '#default_value' => $model_modelentity_type->label,
    '#description'   => t('The human-readable name of this ELabel type.'),
    '#required'      => TRUE,
    '#size'          => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type'          => 'machine_name',
    '#default_value' => isset($model_modelentity_type->type) ? $model_modelentity_type->type : '',
    '#maxlength'     => 32,
    '#machine_name'  => array(
      'exists' => 'model_modelentity_get_types',
      'source' => array('label'),
    ),
    '#description'   => t(
      'A unique machine-readable name for this ELabel type. It must only contain lowercase letters, numbers, and underscores.'
    ),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Save ELabel type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function model_modelentity_type_form_submit(&$form, &$form_state) {
  $model_modelentity_type = entity_ui_form_submit_build_entity($form, $form_state);
  $model_modelentity_type->save();
  $form_state['redirect'] = 'admin/structure/model/modelentity_types';
}

/**
 * Form API submit callback for the delete button.
 */
function model_modelentity_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/model/modelentity_types/manage/' . $form_state['model_modelentity_type']->type . '/delete';
}
