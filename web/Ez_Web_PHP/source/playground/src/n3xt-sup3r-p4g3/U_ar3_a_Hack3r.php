<?php
// Check if the 'flag' GET parameter is set
$delay = 0.5;
$url = '/?message=Can you see it? LOL';

echo "<html><head><meta http-equiv='refresh' content='$delay;url=$url'></head><body></body></html>";

echo "Flag is set and correct. Have you seen that flag yet? Find it before we go.<br>";
?>