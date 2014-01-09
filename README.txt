Installation Instructions:

1. Copy the zoho module directory into your modules directory.

2. Enable zoho module at: Administer > Modules (admin/modules)

3. Go to Administer > People > Permissions (admin/people/permissions) 
   and grant 'Administer zoho api module' permission to the needed user roles.

4. Configure Zoho CRM account settings at admin/config/services/zoho

Usage Instructions:

To store data from drupal to zoho crm, use 
 store_data_to_crm($type, $xml, $update_id = NULL);

 @params
 $type : Type of records to be added. e.g,'Leads'
 $xml  : The xml data to be stored in zoho crm.
    Please check the link below for more information on xml format.
    https://www.zoho.com/crm/help/api/api-methods.html
 $update_id : Optional-the Id of the record to be updated.
              If specified Updates the data already present in crm.
 Return Value :
    Returns an object with following keys:
    success will contain TRUE/FALSE which determines if the request is succesfull or not.
    error will contain error code if the request was not successfull.
    message will contain success message or error message.
    records will contain an array with details of the inserted records if the request is successfull.

To fetch records from zoho crm, use
 get_records_zoho($search_condition, $type = 'Leads', $select_columns = 'All');

 @params
 $search_condition : search condition based on which records will be fetched.
                     e.g,'(Email|=|xyz@xyz.com)'
 $type : Type of records to be fetched. e.g,'Leads'
 $select_columns = Columns of the records to be fetched.
                   e.g, 'Leads(First Name,Last Name,Email)'
 Return Value : 
    Returns an object with following keys:
    success will contain TRUE/FALSE which determines if the request is succesfull or not.
    error will contain error code if the request was not successfull.
    message will contain success message or error message.
    records will contain an associated array of records with data if the request is successfull.


Author:
Chakrapani Reddivari
chakrapani@azrisolutions.com
