<?php
require_once "config.inc.php";

function getQuantityOfLines(string $dirPath): ?array
{
    $fileSizes = null;
    $sortedFiles = getSortedFiles($dirPath);
    foreach ($sortedFiles as $type => $category) {
        $fileSizes[$type] = 0;
        foreach ($category as $fileByCategory) {
            $fileSizes[$type] += sizeof(file($dirPath . '/' . $fileByCategory));
        }
    }

    return $fileSizes;
}

function getSortedFiles(string $dirPath): ?array
{
    $fileNames = scandir($dirPath);
    if (!$fileNames) {
        return null;
    }
    $sortedFiles = initTypes();
    $fileNames = array_diff($fileNames, array('..', '.'));

    foreach ($fileNames as $fileName) {
        foreach ($sortedFiles as $type => &$sortedFile) {
            addFileNameByExtension($fileName, $type,  $sortedFile);
        }
    }

    return $sortedFiles;
}

function initTypes(): array
{
    $types = [];
    foreach (ALL_TYPES as $type) {
        $types[$type] = [];
    }

    return $types;
}

function getExtension(string $filename): ?string
{
    $path_info = pathinfo($filename);
    return $path_info['extension'];
}

function addFileNameByExtension(string $fileName, string $extension, array &$source): void
{
    if (getExtension($fileName) == $extension) {
        $source[] = $fileName;
    }
}