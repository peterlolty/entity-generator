<?php

/**
 * @file
 * Modelentity editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring
 * instead to use views. That offers more flexibility to change a UI that
 * will, more often than not, be end-user facing.
 */

/**
 * UI controller.
 */
class ModelentityUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    // Change the add page menu to multiple types of entities.
    $items[$this->path . '/add'] = array(
      'title'            => 'Add a ELabel',
      'description'      => 'Add a new ELabel',
      'page callback'    => 'model_modelentity_add_page',
      'access callback'  => 'model_modelentity_access',
      'access arguments' => array('create'),
      'type'             => MENU_NORMAL_ITEM,
      'weight'           => 20,
      'file'             => 'includes/model_modelentity.admin.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']),
    );

    // Add menu items to add each different type of entity.
    foreach (model_modelentity_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title'            => 'Add ' . $type->label,
        'page callback'    => 'model_modelentity_form_wrapper',
        'page arguments'   => array(model_modelentity_create(array('type' => $type->type))),
        'access callback'  => 'model_modelentity_access',
        'access arguments' => array('create', (object) array('type' => $type->type)),
        'file'             => 'includes/model_modelentity.admin.inc',
        'file path'        => drupal_get_path('module', $this->entityInfo['module']),
      );
    }

    // Loading and editing model_modelentity entities.
    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title'   => 'Edit',
      'type'    => MENU_DEFAULT_LOCAL_TASK,
      'page callback'    => 'model_modelentity_form_wrapper',
      'page arguments'   => array($id_count),
      'access callback'  => 'model_modelentity_access',
      'access arguments' => array('edit', $id_count),
      'weight'           => -10,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file'             => 'includes/model_modelentity.admin.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']),
    );

    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title'            => 'Delete',
      'page callback'    => 'model_modelentity_delete_form_wrapper',
      'page arguments'   => array($id_count),
      'access callback'  => 'model_modelentity_access',
      'access arguments' => array('delete', $id_count),
      'type'             => MENU_LOCAL_TASK,
      'context'          => MENU_CONTEXT_INLINE,
      'weight'           => 10,
      'file'             => 'includes/model_modelentity.admin.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']),
    );

    // Menu item for viewing model_modelentities.
    $items[$this->path . '/' . $wildcard] = array(
      // 'title' => 'Title',
      'title callback'   => 'model_modelentity_page_title',
      'title arguments'  => array($id_count),
      'page callback'    => 'model_modelentity_page_view',
      'page arguments'   => array($id_count),
      'access callback'  => 'model_modelentity_access',
      'access arguments' => array('view', $id_count),
      'type'             => MENU_CALLBACK,
    );

    return $items;
  }

  /**
   * Create the markup for the add Modelentity Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('model_modelentity_add_list', array('content' => $content));
  }
}

/**
 * Form callback wrapper: create or edit a model_modelentity.
 *
 * @param object $model_modelentity
 *   The model_modelentity object being edited by this form.
 *
 * @return array
 *   Form.
 *
 * @see model_modelentity_edit_form()
 */
function model_modelentity_form_wrapper($model_modelentity) {
  // Add the breadcrumb for the form's location.
  //model_modelentity_set_breadcrumb();

  return drupal_get_form('model_modelentity_edit_form', $model_modelentity);
}

/**
 * Form callback wrapper: delete a model_modelentity.
 *
 * @param object $model_modelentity
 *   The model_modelentity object being edited by this form.
 *
 * @return array
 *   Form.
 *
 * @see model_modelentity_edit_form()
 */
function model_modelentity_delete_form_wrapper($model_modelentity) {
  // Add the breadcrumb for the form's location.
  //model_modelentity_set_breadcrumb();
  return drupal_get_form('model_modelentity_delete_form', $model_modelentity);
}

/**
 * Form callback: create or edit a model_modelentity.
 *
 * @param object $model_modelentity
 *   The model_modelentity object to edit or for a create form an empty
 *     model_modelentity object with only a model_modelentity type defined.
 */
function model_modelentity_edit_form($form, &$form_state, $model_modelentity) {
  // Add the default field elements.
  /*$form['name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('ELabel Name'),
    '#default_value' => isset($model_modelentity->name) ? $model_modelentity->name : '',
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#weight'        => -5,
  );*/

  // Add the field related form elements.
  $form_state['model_modelentity'] = $model_modelentity;
  field_attach_form('model_modelentity', $model_modelentity, $form, $form_state);

  $form['actions'] = array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight'     => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Save'),
    '#submit' => $submit + array('model_modelentity_edit_form_submit'),
  );

  if (!empty($model_modelentity->name)) {
    $form['actions']['delete'] = array(
      '#type'   => 'submit',
      '#value'  => t('Delete'),
      '#suffix' => l(t('Cancel'), 'model/modelentities'),
      '#submit' => $submit + array('model_modelentity_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'model_modelentity_edit_form_validate';

  return $form;
}

/**
 * Implements hook_form_validate().
 */
function model_modelentity_edit_form_validate(&$form, &$form_state) {
  $model_modelentity = $form_state['model_modelentity'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('model_modelentity', $model_modelentity, $form, $form_state);
}

/**
 * Implements hook_form_submit().
 *
 * @todo remove hard-coded link
 */
function model_modelentity_edit_form_submit(&$form, &$form_state) {

  $model_modelentity = entity_ui_controller('model_modelentity')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the model_modelentity and go back to the list of model_modelentities.

  // Add in created and changed times.
  if ($model_modelentity->is_new = isset($model_modelentity->is_new) ? $model_modelentity->is_new : 0) {
    $model_modelentity->created = REQUEST_TIME;
  }

  $model_modelentity->changed = REQUEST_TIME;

  $model_modelentity->save();
  $form_state['redirect'] = 'model/modelentities';
}

/**
 * Form API submit callback for the delete button.
 * @todo Remove hard-coded path
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 */
function model_modelentity_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'model/modelentities/' . $form_state['model_modelentity']->model_modelentity_id . '/delete';
}

/**
 * Form callback: confirmation form for deleting a model_modelentity.
 *
 * @param object $model_modelentity
 *   The model_modelentity to delete
 *
 * @return array
 *   Form.
 *
 * @see confirm_form()
 */
function model_modelentity_delete_form($form, &$form_state, $model_modelentity) {
  $form_state['model_modelentity'] = $model_modelentity;

  $form['#submit'][] = 'model_modelentity_delete_form_submit';

  $form = confirm_form(
    $form,
    t('Are you sure you want to delete ELabel %name?', array('%name' => $model_modelentity->name)),
    'model/modelentities',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function model_modelentity_delete_form_submit($form, &$form_state) {
  $model_modelentity = $form_state['model_modelentity'];

  model_modelentity_delete($model_modelentity);

  drupal_set_message(t('The ELabel %name has been deleted.', array('%name' => $model_modelentity->name)));
  watchdog('model', 'Deleted ELabel %name.', array('%name' => $model_modelentity->name));

  $form_state['redirect'] = 'model/modelentities';
}


/**
 * Page to add Modelentity Entities.
 * @todo Pass this through a proper theme function
 *
 * @return mixed
 *   Page.
 */
function model_modelentity_add_page() {
  $controller = entity_ui_controller('model_modelentity');

  return $controller->addPage();
}


/**
 * Displays the list of available model_modelentity types for model_modelentity creation.
 *
 * @ingroup themeable
 */
function theme_model_modelentity_add_list($variables) {
  $content = $variables['content'];

  if ($content) {
    $output = '<dl class="model_modelentity-type-list">';

    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer model model_modelentity types')) {
      $output = '<p>' . t(
          'ELabel Entities cannot be added because you have not created any ELabel types yet. Go to the <a href="@create-model_modelentity-type">ELabel type creation page</a> to add a new ELabel type.',
          array('@create-model_modelentity-type' => url('admin/structure/model/modelentity_types/add'))
        ) . '</p>';
    }
    else {
      $output = '<p>' . t('No ELabel types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative model_modelentity pages.
 */
function model_modelentity_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('module_name'), 'model'),
    l(t('ELabels'), 'model/modelentities'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
