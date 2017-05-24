<?php

/**
 * Implements hook_views_default_views().
 */
function model_modelentity_include_default_views() {

  $view = new view;
  $view->name = 'model_modelentity_admin';
  $view->description = 'A list of all ELabels';
  $view->tag = 'ELabels';
  $view->base_table = 'model_modelentity';
  $view->human_name = 'ELabels Admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ELabels';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer model model_modelentities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'model_modelentity_id' => 'model_modelentity_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'model_modelentity_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No ELabel have been created yet';
  /* Field: Modelentity: Modelentity ID */
  $handler->display->display_options['fields']['model_modelentity_id']['id'] = 'model_modelentity_id';
  $handler->display->display_options['fields']['model_modelentity_id']['table'] = 'model_modelentity';
  $handler->display->display_options['fields']['model_modelentity_id']['field'] = 'model_modelentity_id';
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['model_modelentity_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['model_modelentity_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['model_modelentity_id']['empty_zero'] = 0;
  /* Field: Modelentity: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'model_modelentity';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  /* Field: Modelentity: Link */
  $handler->display->display_options['fields']['link_model_modelentity']['id'] = 'link_model_modelentity';
  $handler->display->display_options['fields']['link_model_modelentity']['table'] = 'model_modelentity';
  $handler->display->display_options['fields']['link_model_modelentity']['field'] = 'link_model_modelentity';
  $handler->display->display_options['fields']['link_model_modelentity']['label'] = 'View';
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_model_modelentity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_model_modelentity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_model_modelentity']['empty_zero'] = 0;
  /* Field: Modelentity: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'model_modelentity';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'model_modelentity_admin_page');
  $handler->display->display_options['path'] = 'model/modelentities';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'ELabels';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'ELabels';
  $handler->display->display_options['tab_options']['description'] = 'Manage ELabels';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['model_modelentity_admin'] = array(
    t('Master'),
    t('ELabels'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Empty '),
    t('No ELabel have been created yet'),
    t('Modelentity ID'),
    t('.'),
    t(','),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );

  return $view;
}

