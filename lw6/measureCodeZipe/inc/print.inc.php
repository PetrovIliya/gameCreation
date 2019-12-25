<?php

function printSizesInfo(array $sizesInfo): void
{
    foreach ($sizesInfo as $key => $fileSize) {
        echo $key . ': ' . $fileSize . PHP_EOL;
    }
}
