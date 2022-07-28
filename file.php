<!DOCTYPE html>
<html>
<body>

<?php

$secret = "FOEIUWGHFEEUHOFUOIU";
    if(array_key_exists("submit", $_POST)){
        if($secret == $_POST['secret']) {
        print "Access granted. The password for natas7 is <censored>";
    } else {
        print "Wrong secret";
    }
}

?>

</body>
</html>

<!-- 
Natas8
DBfUBfqQG69KvJvJ1iAbMoIpwSNQ9bWe -->


<?php
  
$str = "3d3d516343746d4d6d6c315669563362";

$newstr = pack("H*", $str);

$rev = strrev($newstr);

$deco = base64_decode($rev);

echo $deco;

?>
