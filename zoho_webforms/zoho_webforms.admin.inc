<?php

/**
 * @file
 * Defines admin configuration page for the Zoho Webforms module
 */

/**
 * Menu callback for admin/config/zoho. Admin settings form.
 */
function zoho_webforms_admin_settings_form($form, &$form_state) {
  $form = array();
  $form['zoho_webforms_module'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoho module name'),
    '#default_value' => variable_get('zoho_webforms_module', ''),
    '#description' => t('Enter the Zoho module name you wish to use (e.g., Leads, CustomModule1, etc.)'),
  );
  $form['zoho_webforms_form_ids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Webforms to submit'),
    '#options' => get_webform_ids(),
    '#default_value' => array_keys(array_filter(variable_get('zoho_webforms_form_ids', array()))),
  );
  $form['zoho_webforms_mapping'] = array(
    '#type' => 'textarea',
    '#title' => t('Field mapping from Drupal -> Zoho. Enter one per line as webform_field_name|zoho_field_name'),
    '#default_value' => variable_get('zoho_webforms_mapping', ''),
  );
  $form['zoho_webforms_other_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Other Zoho field values (one per line; Zoho field name|value)'),
    '#default_value' => variable_get('zoho_webforms_other_fields', ''),
  );
  $form['#validate'][] = 'zoho_webforms_validate_settings';
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Settings'),
  );
  return $form;
}

/**
 * Validate function for admin settings form.
 */
function zoho_webforms_validate_settings($form, &$form_state) {
}

/**
 * Submit function for admin settings form.
 */
function zoho_webforms_admin_settings_form_submit($form, &$form_state) {
  $keys = array(
    'zoho_webforms_module',
    'zoho_webforms_form_ids',
    'zoho_webforms_mapping',
    'zoho_webforms_other_fields',
  );
  foreach ($keys as $key) {
    variable_set($key, $form_state['values'][$key]);
  }
}

// return id => name
function get_webform_ids() {
  $forms = array();
  $result = db_query('SELECT webform.nid AS nid, node.title AS title FROM webform JOIN node ON webform.nid = node.nid');
  foreach ($result as $record) {
    $forms[$record->nid] = $record->title;
  }
  return $forms;
}
