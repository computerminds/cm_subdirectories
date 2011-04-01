<?php

function cm_subdirectories_hosting_site_context_options(&$task) {
  $task->context_options['subfolder_path'] = $task->ref->subfolder_path;
}

function cm_subdirectories_drush_context_import($context, &$node) {
  if ($context->type == 'site') {
    $node->subfolder_path = $context->subfolder_path;
  }

}
