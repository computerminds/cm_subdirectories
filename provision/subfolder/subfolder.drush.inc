<?php

/**
 * @file
 *   The subfolder provision service.
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

/**
 * The subfolder service base class.
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

/**
 * Implementation of hook_provision_apache_vhost_config().
 *
 * Add instructions for mod_rewrite to remove the subfolder path.
 * This will result in the following lines in virtual host files:
 * <code>
 *   RewriteEngine On
     RewriteOptions inherit
     RewriteRule ^/SUBFOLDER(/?)$ /index.php
     RewriteRule ^/SUBFOLDER(/.*)$ $1
 * </code>
 */
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

/**
 * Implementation of hook_provision_drupal_config().
 *
 * Add the subfolder to the $base_url because Drupal won't pick it up
 * automatically.
 * This will result in the following code in the settings.php:
 * <code>
 *   $base_url = 'http://site-url.domain/SUBFOLDER';
 * </code>
 */
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
