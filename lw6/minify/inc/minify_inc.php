<?php
const SOURCE_FOLDER = '/web/css/';
const RESULT_FOLDER = '/web/css.min/';
const CONFIG_FILE = 'minifycss.txt';

function minify($configFile, string $rootPath): void
{
    while (!feof($configFile)) {
        if ($sourceFileName = trim(fgets($configFile))) {
            $sourcePath = $rootPath . RESULT_FOLDER . $sourceFileName;
            if (file_exists($sourcePath)) {
                unlink($sourcePath);
            }
            writeFileContent($configFile, $sourcePath, $rootPath);
        }
    }
}

function getFileContent(string $filePath): string
{
    $fileContent = file($filePath, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
    $fileContent = ($fileContent) ? array_map('trim', $fileContent) : '';
    $fileContent = ($fileContent) ? implode($fileContent) : '';
    $fileContent = preg_replace("/\s+/"," ", $fileContent);
    $fileContent = preg_replace('/;}/','}', $fileContent);

    return preg_replace('/ {/','{', $fileContent);
}

function writeFileContent($configFile, string $sourcePath, string $rootPath): void
{
    while ($internalFileName = trim(fgets($configFile))) {
        $internalFilePath = $rootPath . SOURCE_FOLDER . $internalFileName;
        $internalFileContent = getFileContent($internalFilePath);
        file_put_contents($sourcePath, $internalFileContent, FILE_APPEND);
    }
}