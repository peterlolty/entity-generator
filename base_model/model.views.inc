<?php

/**
 * @file
 * Providing extra functionality for the Modelentity UI via views.
 */

/**
 * Implements hook_views_data().
 */
function model_views_data_alter(&$data) {

  $data['model_modelentity']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field'      => 'uid',
    ),
  );

  $data['model_modelentity']['uid'] = array(
    'title'        => t('User ID'),
    'help'         => t('The author ID'),
    'relationship' => array(
      // The name of the table to join with.
      'base'       => 'users',
      // The name of the field on the joined table.
      'base field' => 'uid',
      'handler'    => 'views_handler_relationship',
      'label'      => t('Author ID of the ELabel (relationship)'),
      'title'      => t('Author ID'),
      'help'       => t('Author of the ELabel (relationship)'),
    ),
    'field'        => array('handler' => 'views_handler_field_numeric', 'click sortable' => TRUE),
    'filter'       => array('handler' => 'views_handler_filter_numeric'),
    'sort'         => array('handler' => 'views_handler_sort'),
    'argument'     => array('handler' => 'views_handler_argument_numeric'),
  );

  $data['model_modelentity']['link_model_modelentity'] = array(
    'field' => array(
      'title'   => t('Link'),
      'help'    => t('Provide a link to the model_modelentity.'),
      'handler' => 'model_modelentity_handler_link_field',
    ),
  );
  $data['model_modelentity']['edit_model_modelentity'] = array(
    'field' => array(
      'title'   => t('Edit Link'),
      'help'    => t('Provide a link to the edit form for the model_modelentity.'),
      'handler' => 'model_modelentity_handler_edit_link_field',
    ),
  );
  $data['model_modelentity']['delete_model_modelentity'] = array(
    'field' => array(
      'title'   => t('Delete Link'),
      'help'    => t('Provide a link to delete the model_modelentity.'),
      'handler' => 'model_modelentity_handler_delete_link_field',
    ),
  );

  // This content of this field are decided based on the menu structure that
  // follows model/modelentities/%model_modelentity_id/op
  $data['model_modelentity']['operations'] = array(
    'field' => array(
      'title'   => t('Operations links'),
      'help'    => t('Display all operations available for this model_modelentity.'),
      'handler' => 'model_modelentity_handler_model_modelentity_operations_field',
    ),
  );

  $data['model_modelentity']['created'] = array(
    'title'  => t('Created'),
    'help'   => t('Creation date'),
    'field'  => array(
      'handler'        => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort'   => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['model_modelentity']['changed'] = array(
    'title'  => t('Changed'),
    'help'   => t('Last modification date'),
    'field'  => array(
      'handler'        => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort'   => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
}

