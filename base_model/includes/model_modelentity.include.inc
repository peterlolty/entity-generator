<?php

/**
 * Determines whether the given user has access to a model_modelentity.
 *
 * @param string $op
 *   The operation being performed. One of 'view', 'update', 'create', 'delete'
 *   or just 'edit' (being the same as 'create' or 'update').
 * @param object $model_modelentity
 *   Optionally a model_modelentity or a model_modelentity type to check access for.
 *   If nothing is given, access for all model_modelentities is determined.
 * @param object $account
 *   The user to check for. Leave it to NULL to check for the global user.
 *
 * @return bool
 *   Whether access is allowed or not.
 */
function model_modelentity_access($op, $model_modelentity = NULL, $account = NULL) {
  if (user_access('administer model model_modelentities', $account)) {
    return TRUE;
  }

  switch($op){
    case 'create':
    case 'new':
      $op = 'create';
    break;

    case 'edit':
    case 'update':
      $op = 'edit';
    break;

    case 'view':
    case 'list':
      $op = 'view';
    break;

    case 'delete':
    case 'remove':
      $op = 'delete';
    break;

    default:
      $op = 'void';
    break;
  }

  if (isset($model_modelentity) && is_object($model_modelentity) && isset($model_modelentity->type)) {
    $type_name = $model_modelentity->type;
    if (user_access("$op any model $type_name model_modelentity", $account)) {
      return TRUE;
    }
    if (isset($model_modelentity->uid) && $model_modelentity->uid == (isset($account) ? $account->uid : $GLOBALS['user']->uid)) {
      if (user_access("$op own model $type_name model_modelentity", $account)) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/**
 * Access callback for the entity API.
 */
function model_modelentity_type_access($op, $type = NULL, $account = NULL) {
  return user_access('administer model model_modelentity types', $account);
}

/**
 * Gets an array of all model_modelentity types, keyed by the type name.
 *
 * @param string $type_name
 *   If set, the type with the given name is returned.
 *
 * @return ModelentityType[]
 *   Depending whether $type isset, an array of model_modelentity types
 *   or a single one.
 */
function model_modelentity_get_types($type_name = NULL) {
  // entity_load will get the Entity controller for our model_modelentity entity
  // and call the load function of that object - we are loading entities
  // by name here.
  $types = entity_load_multiple_by_name('model_modelentity_type', isset($type_name) ? array($type_name) : FALSE);

  return isset($type_name) ? reset($types) : $types;
}

/**
 * Menu argument loader; Load a model_modelentity type by string.
 *
 * @param string $type
 *   The machine-readable name of a model_modelentity type to load.
 *
 * @return array|bool
 *   A model_modelentity type array or FALSE if $type does not exist.
 */
function model_modelentity_type_load($type) {
  return model_modelentity_get_types($type);
}

/**
 * Fetch a model_modelentity object; make sure that the wildcard you choose
 * in the model_modelentity entity definition fits the function name here.
 *
 * @param int $model_modelentity_id
 *   Integer specifying the model_modelentity id.
 * @param bool $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return object|bool
 *   A fully-loaded $model_modelentity object or FALSE if it cannot be loaded.
 *
 * @see model_modelentity_load_multiple()
 */
function model_modelentity_load($model_modelentity_id, $reset = FALSE) {
  $model_modelentities = model_modelentity_load_multiple(array($model_modelentity_id), array(), $reset);

  return reset($model_modelentities);
}

/**
 * Load multiple model_modelentities based on certain conditions.
 *
 * @param array $model_modelentity_ids
 *   An array of model_modelentity IDs.
 * @param array $conditions
 *   An array of conditions to match against the {model_modelentity} table.
 * @param bool $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return array
 *   An array of model_modelentity objects, indexed by model_modelentity_id.
 *
 * @see entity_load()
 * @see model_modelentity_load()
 */
function model_modelentity_load_multiple($model_modelentity_ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('model_modelentity', $model_modelentity_ids, $conditions, $reset);
}

/**
 * Deletes a model_modelentity.
 *
 * @param \Modelentity $model_modelentity
 *   Entity model.
 */
function model_modelentity_delete(Modelentity $model_modelentity) {
  $model_modelentity->delete();
}

/**
 * Delete multiple model_modelentities.
 *
 * @param array $model_modelentity_ids
 *   An array of model_modelentity IDs.
 */
function model_modelentity_delete_multiple(array $model_modelentity_ids) {
  entity_get_controller('model_modelentity')->delete($model_modelentity_ids);
}

/**
 * Create a model_modelentity object.
 *
 * @param array $values
 *   An array of values.
 */
function model_modelentity_create($values = array()) {
  return entity_get_controller('model_modelentity')->create($values);
}

/**
 * Saves a model_modelentity to the database.
 *
 * @param \Modelentity $model_modelentity
 *   The model_modelentity object.
 */
function model_modelentity_save(Modelentity $model_modelentity) {
  return $model_modelentity->save();
}

/**
 * Saves a model_modelentity type to the db.
 *
 * @param \ModelentityType $type
 *   The model_modelentity type object.
 */
function model_modelentity_type_save(ModelentityType $type) {
  $type->save();
}

/**
 * Deletes a model_modelentity type from the db.
 *
 * @param \ModelentityType $type
 *   The model_modelentity type object.
 */
function model_modelentity_type_delete(ModelentityType $type) {
  $type->delete();
}

/**
 * URI callback for model_modelentities.
 *
 * @param \Modelentity $model_modelentity
 *   The model_modelentity object.
 *
 * @return array
 *   URI callback.
 */
function model_modelentity_uri(Modelentity $model_modelentity) {
  return array(
    'path' => 'model/modelentities/' . $model_modelentity->model_modelentity_id,
  );
}

/**
 * Menu title callback for showing individual entities.
 *
 * @param \Modelentity $model_modelentity
 *   The model_modelentity object.
 *
 * @return string
 *   Menu title.
 */
function model_modelentity_page_title(Modelentity $model_modelentity) {
  return $model_modelentity->name;
}

/**
 * Sets up content to show an individual model_modelentity.
 * @todo - get rid of drupal_set_title();
 *
 * @param \Modelentity $model_modelentity
 *   The model_modelentity object.
 * @param string $view_mode
 *   View mode.
 *
 * @return mixed
 *   Content.
 */
function model_modelentity_page_view(Modelentity $model_modelentity, $view_mode = 'full') {
  $controller = entity_get_controller('model_modelentity');
  $content = $controller->view(array($model_modelentity->model_modelentity_id => $model_modelentity));
  drupal_set_title($model_modelentity->name);

  return $content;
}

/**
 * Callback to get $model_modelentity->user.
 *
 * @see model_modelentity_entity_property_info().
 */
function model_modelentity_property_user_get(Modelentity $model_modelentity, array $options, $property_name, $entity_type) {
  if (is_numeric($model_modelentity->uid)) {
    $entity = entity_load_single('user', $model_modelentity->uid);
    return entity_metadata_wrapper('user', $entity);
  }
}

/**
 * Callback to set $model_modelentity->user that supports null value.
 */
function model_modelentity_property_user_set(Modelentity $model_modelentity, $name, $value, $lang, $type, $info) {
  if (is_object($value) && $account = $value->value()) {
    $model_modelentity->{$info['schema field']} = $account->uid;
  }
  else {
    $model_modelentity->{$info['schema field']} = NULL;
  }
}

/**
 * Return an associative array of model_modelentity types to be used as an options list.
 *
 * @return array
 *   Keyed by name with a label value.
 */
function model_modelentity_type_options_list() {
  $options = array();
  foreach (model_modelentity_get_types() as $type) {
    $options[$type->type] = $type->label;
  }

  return $options;
}

if (class_exists('EntityInlineEntityFormController')) {
  /**
   * The Controller for Modelentity entities for Inline Entity Form.
   *
   * Class ModelentityInlineEntityFormController
   */
  class ModelentityInlineEntityFormController extends EntityInlineEntityFormController {

  }
}
