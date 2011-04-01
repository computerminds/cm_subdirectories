<?php
/**
 *   $Id$
 */

/**
 * @file
 *   Example service implementation for the hosting front end.
 */

/**
 * The base service type class , registered with hook_hosting_service_type.
 */
class hostingService_subfolder extends hostingService {
 /**
 *   the value stored in the service column of hosting_service table.
 */
  public $service = 'subfolder';
}


/**
 * An implementation of the example service type, registered with hook_hosting_service.
 */

class hostingService_subfolder_basic extends hostingService_subfolder {
 /**
  *   the value stored in the type column of the hosting_service table.
  */
  public $type = 'basic';

 /**
  *   node operations
  */

}
