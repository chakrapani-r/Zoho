Installation Instructions:

1. Copy the zoho module directory into your modules directory.

2. Enable zoho module at: Administer > Site building > Modules

3. Configure Zoho CRM account settings at admin/config/services/zoho-settings

Usage Instructions:

To store data from drupal to zoho crm, use 
 store_data_to_crm($type, $xml, $update_id = NULL);

 @params
 $type : Type of records to be added. e.g,'Leads'
 $xml  : The xml data to be stored in zoho crm.
    Please check the link below for more information on xml format.
    https://zohocrmapi.wiki.zoho.com/API-Methods.html
 $update_id : Optional-the Id of the record to be updated.
              If specified Updates the data already present in crm.
 Returns Value :Returns the status/response message of the request.

To fetch records from zoho crm, use
 get_records_zoho($search_condition, $type = 'Leads', $select_columns = 'All');

 @params
 $search_condition : search condition based on which records will be fetched.
                     e.g,'(Email|=|xyz@xyz.com)'
 $type : Type of records to be fetched. e.g,'Leads'
 $select_columns = Columns of the records to be fetched.
                   e.g, 'Leads(First Name,Last Name,Email)'
 Returns Value : Error message if error occurs, Otherwise returns an array.

Author:
Chakrapani Reddivari
chakrapani@azrisolutions.com
