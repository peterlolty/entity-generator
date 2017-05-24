<?php

/**
 * @file
 * @see hook_entity_property_info()
 */
class ModelentityMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['model_modelentity_id'] = array(
      'label' => t("ELabel ID"),
      'type' => 'integer',
      'description' => t("The unique ID of the modelentity."),
      'schema field' => 'model_modelentity_id',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['type'] = array(
      'label' => t("Type"),
      'type' => 'token',
      'description' => t("The type of the modelentity."),
      'options list' => 'model_modelentity_type_options_list',
      'required' => TRUE,
      'schema field' => 'type',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['label'] = array(
      'label' => t("Label"),
      'type' => 'text',
      'description' => t("The label of the modelentity."),
      'schema field' => 'name',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['created'] = array(
      'label' => t("Created"),
      'type' => 'date',
      'description' => t("The date the modelentity was created."),
      'schema field' => 'created',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['changed'] = array(
      'label' => t("Changed"),
      'type' => 'date',
      'description' => t("The date the modelentity was most recently changed."),
      'schema field' => 'changed',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['user'] = array(
      'label' => t("User"),
      'type' => 'user',
      'description' => t("The user who created the modelentity."),
      'schema field' => 'uid',
      'getter callback' => 'model_modelentity_property_user_get',
      'setter callback' => 'model_modelentity_property_user_set',
    );

    return $info;
  }

}
