<?php
// $Id$

/**
 * @file
 *   An example of the provision service API.
 *
 *  Declares a new service type and a basic implementation of it.
 *  It matches the same service definition in the hosting front end.
 */

include_once(dirname(__FILE__) . '/../provision.service.inc');

/**
 * Expose the service type this extension defines to provision.
 *
 * Implementations are then conditionally loaded when the option
 * "--$service_service_type=$type" is passed to the provision-save
 * command of a server.
 *
 * Implementations are automatically loaded from :
 * provision/$service/$type/$type_service.inc.
 *
 * @return
 *   An array with the service type the key, and the default implementation the value.
 */
function subfolder_provision_services() {
  return array('subfolder' => NULL);
}

function subfolder_provision_apache_vhost_config($uri, $data) {
  $lines = array();
  if (d()->type == 'site') {
    if (!empty(d()->subfolder_path)) {
      $lines[] = 'RewriteEngine On';
      $lines[] = 'RewriteOptions inherit';
      $lines[] = 'RewriteRule ^/' . d()->subfolder_path . '(/?)$ /index.php';
      $lines[] = 'RewriteRule ^/' . d()->subfolder_path . '(/.*)$ $1';
    }
  }

  return implode($lines, "\n");
}

function subfolder_provision_drupal_config($uri, $data) {
  $lines = array();
  if (d()->type == 'site') {
    if (!empty(d()->subfolder_path)) {
      $lines[] = '// Fix the basepath to include the subfolder structure.';
      $lines[] = '$base_url = \'http://' . $uri . '/' . d()->subfolder_path . '\';';

    }
  }
  return implode($lines, "\n");
}

/**
 * The service type base class.
 *
 * All implementations of the service type will inherit this class.
 * This class should define the 'public API' to be used by the rest
 * of the system, which should not expose implementation details.
 */
class provisionService_subfolder extends provisionService {
  public $service = 'subfolder';

  /**
   * Register the db handler for sites, based on the db_server option.
   */
  static function subscribe_site($context) {
    $context->setProperty('subfolder_path');
  }
}
