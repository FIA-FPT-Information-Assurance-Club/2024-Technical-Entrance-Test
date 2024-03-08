<?php
// Check if isset GET pass-code
if (isset($_GET['pass-code'])) {
    // Check if GET pass-code is equal to the string
    if ($_GET['pass-code'] === 'nquangit') {
        // If true, echo the flag
        echo 'Flag: XzNANXlfVDBfMHYzcmMwbTNf';
        $delay = 0.1;
        $url = '/?message=Final part:%20you%20must%20send%20a%20post%20request%20to%20%2Fget%5Ff1nal%5Ffl4g%2Ephp%2E%20Data%3A%20%22hacker%3Dme%22%0A';

        echo "<html><head><meta http-equiv='refresh' content='$delay;url=$url'></head><body></body></html>";

        echo "Flag is set and correct. Have you seen that flag yet? Find it before we go.<br>";

    } else {
        header('Location: /s3cr3t_f0ld3r');
    }
} else {
    header('Location: /s3cr3t_f0ld3r');
}
?>