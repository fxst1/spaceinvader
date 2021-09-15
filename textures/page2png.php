<?php

function transparentPaintImage($filename, $color, $alpha, $fuzz) {
    $imagick = new \Imagick(realpath($filename));

    //Need to be in a format that supports transparency
    $imagick->setimageformat('png');

    $imagick->transparentPaintImage(
        $color, $alpha, $fuzz * \Imagick::getQuantum(), false
    );

    //Not required, but helps tidy up left over pixels
    $imagick->despeckleimage();

$imagick->writeImage("$filename.update.png");

//    header("Content-Type: image/png");
//    echo $imagick->getImageBlob();
}

transparentPaintImage($argv[1], '#ffffff', 1.0, 0.0);




?>
