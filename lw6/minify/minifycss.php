<?php
require_once('inc/minify_inc.php');

$rootPath = __DIR__;
$file = fopen($rootPath . '/' . CONFIG_FILE, 'r');
if ($file) {
    minify($file, $rootPath);
}