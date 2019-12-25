<?php
require_once "inc/config.inc.php";

function getFileSizes(string $dirPath): ?array
{
    $fileSizes = null;
    $sortedFiles = getSortedFiles($dirPath);
    $sortedFiles = getFilledCategories($sortedFiles);
    foreach ($sortedFiles as $type => $category) {
        $fileSizes[$type] = 0;
        foreach ($category as $fileByCategory) {
            $fileSizes[$type] += filesize($dirPath . '/' . $fileByCategory);
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

function getFilledCategories(?array &$sortedFiles): ?array
{
    foreach ($sortedFiles as $key => $category) {
        if (empty($category)) {
            unset($sortedFiles[$key]);
        }
    }

    return $sortedFiles;
}