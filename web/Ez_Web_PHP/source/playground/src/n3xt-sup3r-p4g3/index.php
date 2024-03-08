<?php

if (isset($_GET['flag'])) {
    // Check if 'flag' equals 'RklBezF0XzE1X3Mw'
    if ($_GET['flag'] == 'RklBezF0XzE1X3Mw') {
        // The 'flag' parameter is set and equals 'RklBezF0XzE1X3Mw'
// The URL you want to redirect to
        $url = '/n3xt-sup3r-p4g3/U_ar3_a_Hack3r.php';

        echo "Flag is set and correct. Have you seen that flag yet? Find it before we go.<br>";
        // Use the 'header()' function to send an HTTP Location header
        header('Location: ' . $url);
        
    } else {
        // Redirect to the homepage if the 'flag' parameter is not set
        header('Location: /');
    }
} else {
    // Redirect to the homepage if the 'flag' parameter is not set
    header('Location: /');
}
// End the script to ensure no further output is sent
exit;
?>