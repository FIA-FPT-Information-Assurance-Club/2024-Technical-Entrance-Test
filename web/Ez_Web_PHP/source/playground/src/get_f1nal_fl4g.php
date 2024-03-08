<?php

if (isset($_POST['hacker'])) {
    // Check if 'flag' equals 'RklBezF0XzE1X3Mw'
    if ($_POST['hacker'] == 'me') {
        // The 'flag' parameter is set and equals 'RklBezF0XzE1X3Mw'
        echo "You are truly excellent: dGgxc19jaDRsbDNuZzN9";
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