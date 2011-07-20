<?php

/**
 * @file
 *   The subfolder provision service.
 */

include_once(dirname(__FILE__) . '/../provision.service.inc');

/**
 * Expose the service type this extension defines to provision.
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
   * Add the subfolder_path property to the site context.
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
 *   RewriteEngine On
 *   RewriteOptions inherit
 *   RewriteRule ^/SUBFOLDER(/?)$ /index.php
 *   RewriteRule ^/SUBFOLDER/(.*)$ /path/to/platform/$1
 */
function subfolder_provision_apache_vhost_config($uri, $data) {
  $lines = array();
  if (d()->type == 'site') {
    if (!empty(d()->subfolder_path)) {
      $lines[] = 'RewriteEngine On';
      $lines[] = 'RewriteOptions inherit';
      $lines[] = 'RewriteRule ^/' . d()->subfolder_path . '(/?)$ /index.php';
      $lines[] = 'RewriteRule ^/' . d()->subfolder_path . '/(.*)$ ' . d()->root . '/$1';
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
 *   $base_url = 'http://site-url.domain/SUBFOLDER';
 */
function subfolder_provision_drupal_config($uri, $data) {
  $lines = array();
  if (d()->type == 'site') {
    if (!empty(d()->subfolder_path)) {
      $lines[] = '  // Fix the basepath to include the subfolder structure.';
      $lines[] = '  $base_url = \'http://' . $uri . '/' . d()->subfolder_path . '\';';
      $lines[] = '  // Try to allow for different domains.';
      $lines[] = '  if (isset($_SERVER[\'HTTP_HOST\'])) {';
      $lines[] = '    $base_url = \'http://\' . $_SERVER[\'HTTP_HOST\'] . \'/' . d()->subfolder_path . '\';';
      $lines[] = '  }';

    }
  }
  return implode($lines, "\n");
}
