<?php

/**
 * @file
 * Module for the Model Entity.
 */

/**
 * Implements hook_menu().
 */
function model_menu() {
  $items = array();

  $items['model'] = array(
    'title' => 'module_name',
    'description' => 'Create, edit and delete all module_name items.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access model'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );
  $items['admin/structure/model'] = array(
    'title' => 'module_name',
    'description' => 'Administer module_name items, such as types, etc.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access model administration'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );

  return $items;
}
