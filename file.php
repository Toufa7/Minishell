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
