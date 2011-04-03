<?php

/**
 * The base subfolder service type class, registered with cm_subdirectories_hosting_service_type().
 */
class hostingService_subfolder extends hostingService {
 /**
  * This is a really simple service, which doesn't actually have any methods
  * because we don't interact with the servers at all.
  */

  /**
   * Declare the service type that we represent.
   */
  public $service = 'subfolder';
}
