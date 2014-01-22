<?php

/**
 * @file
 * Defines admin configuration page for the Zoho API module
 */

/**
 * Menu callback for admin/config/zoho. Admin settings form.
 */
function zoho_admin_settings_form($form, &$form_state) {
  $form = array();
  $existing_tokens = l(t('Existing tokens'), ZOHO_TICKET_URL . 'u/h#setting/authtoken', array('attributes' => array('target' => '_blank')));
  $form['zoho_crm_authtoken'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoho API Authtoken'),
    '#default_value' => variable_get('zoho_crm_authtoken', ''),
    '#description' => t('Enter a Valid API Authtoken. To use an existing Authtoken, login to zoho crm and goto')
    . ' ' . $existing_tokens
    . '<br/>' . t('OR') . '<br/>' . t('Leave this blank and enter your zoho crm username and password in the below fieldset to generate a new Authtoken.'),
  );
  $form['zoho_credentials'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Generate new Authtoken'),
    '#collapsible' => TRUE,
    '#collapsed' => (variable_get('zoho_crm_authtoken', 0)),
    '#description' => t('Use this only if you need to generate a new Authtoken. And to generate a new token, the above Authtoken field should be empty.') . '<br/><strong>' . t('Username and password are NOT stored anywhere.') . '</strong>',
  );
  $form['zoho_credentials']['zoho_crm_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoho Username/Email'),
  );
  $form['zoho_credentials']['zoho_crm_pass'] = array(
    '#type' => 'password',
    '#title' => t('Zoho Password'),
  );
  $form['#validate'][] = 'zoho_validate_settings';
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Settings'),
  );
  return $form;
}

/**
 * Validate function for admin settings form.
 */
function zoho_validate_settings($form, &$form_state) {
  if (($form_state['values']['zoho_crm_authtoken'] == '') && (($form_state['values']['zoho_crm_username'] == '') || ($form_state['values']['zoho_crm_pass'] == ''))) {
    form_set_error('', t('Please fill api Authtoken OR both Username & Password to generate a new Authtoken.'));
  }
}

/**
 * Submit function for admin settings form.
 */
function zoho_admin_settings_form_submit($form, &$form_state) {
  // If Authtoken doesn't exist then generate new Authtoken.
  if (($form_state['values']['zoho_crm_authtoken'] == '') && (($form_state['values']['zoho_crm_username'] != '') && ($form_state['values']['zoho_crm_pass'] != ''))) {
    $result = _zoho_generate_authtoken($form_state['values']['zoho_crm_username'], $form_state['values']['zoho_crm_pass']);
    if (isset($result['authtoken'])) {
      drupal_set_message(t('Successfully generated a new Authtoken : :token', array(':token' => $result['authtoken'])));
    }
    else {
      drupal_set_message(t('There was an error: :error.<br/>Please resolve the error and try again.', array(':error' => $result['error'])), 'error');
    }
  }
  elseif ($form_state['values']['zoho_crm_authtoken'] != '') {
    // Update the Authtoken from the admin settings form.
    variable_set('zoho_crm_authtoken', $form_state['values']['zoho_crm_authtoken']);
  }
}
