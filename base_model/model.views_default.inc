<?php

include_once 'includes/views/model_modelentity.views_default.inc';

/**
 * Implements hook_views_default_views().
 */
function model_views_default_views() {
  $export = array();

  $export['model_modelentity_admin'] = model_modelentity_include_default_views();

  return $export;
}

