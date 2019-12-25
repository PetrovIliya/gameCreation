<?php
require_once "inc/common.inc.php";

$dirPath = $argv[1] ?? '';
if (!file_exists($dirPath)) {
    die('Данной директории не существует');
}
$fileSizes = getQuantityOfLines($dirPath);
printSizesInfo($fileSizes);