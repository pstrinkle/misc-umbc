<?php
        # Name: Patrick Trinkle
        # Email: tri1@umbc.edu
        # Course: CMSC433
        # File: edit.php
	# Project: P3
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title>Edit Bookmark</title>
        <link rel="stylesheet" type="text/css" href="style.css" />
        <script type="text/javascript">
          <!--
          function validateForm() {

            var valid = true;

            if (document.getElementById("name").value == "") {
              document.getElementById("name").style.border = '1px solid #ff0000';
              valid = false;
            }

            if (document.getElementById("url").value == "" ) {
              document.getElementById("url").style.border = '1px solid #ff0000';
              valid = false;
            }

            var regex = /^http(|s):\/\//i;

            var results = regex.exec(document.getElementById("url").value);

            if (results == null) {
              var newurl = "http://" + document.getElementById("url").value;
              document.getElementById("url").value = newurl;
            }


            if (valid == false) {
              document.getElementById("valid").innerHTML = '<span style="color: #ff0000;">There have been some errors!</span>';
            }

            return valid;
          }

          // -->
        </script>
    </head>
    <body>
      <div class="form">
        <h1>Edit Bookmark</h1>
<?php
	$id;
	$bookmarkid;

	if($_SERVER['REQUEST_METHOD'] == 'GET') {
		$id = $_GET['bookmark'];	
	}

	if($_SERVER['REQUEST_METHOD'] == 'POST') {
		$id = $_POST['bookmark'];
	}

	$file = "/afs/umbc.edu/users/t/r/tri1/pub/cs433/read-write/bookmarks.dat";
        $ay_of_bookmarks;
        $ay_ctr = 0;	

	// open file
	if ($fp = fopen($file, "r")) {
		while($name = fgets($fp)) {
			$url = fgets($fp);
			$tags = fgets($fp);
			$notes = fgets($fp);
		
			$name = preg_replace('/\n/', '', $name);
			$url = preg_replace('/\n/', '', $url);
			$tags = preg_replace('/\n/', '', $tags);
			$notes = preg_replace('/\n/', '', $notes);

			$hash = md5($url . $name);

			if ($hash == $id) {
				$bookmarkid = $ay_ctr;
			}

			$ay_of_bookmarks[$ay_ctr] = array(title=>$name, url=>$url, tags=>$tags, notes=>$notes, id=>$hash);

			$ay_ctr++;
		}

		fclose($fp);
	}
	else {
		print "<p>Error couldn't open file</p>";
	}

	$bookmark = $ay_of_bookmarks[$bookmarkid];

        if($_SERVER['REQUEST_METHOD'] == 'GET') {
?>
<div id="valid"></div>
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" name="bookmark" method="post" onSubmit="return validateForm()">
    <table>
        <tr>
            <td class="label"><label for="name">Name<sup>&#8224;</sup>:</label></td>
            <td class="input"><input id="name" name="name" value="<?php echo $bookmark[title]; ?>" /></td>
        </tr>
        <tr>
            <td class="label"><label for="url">URL<sup>&#8224;</sup>:</label></td>
            <td class="input"><input id="url" name="url" value="<?php echo $bookmark[url]; ?>" /></td>
        </tr>
        <tr>
            <td class="label"><label for="tags">Tags:</label></td>
            <td class="input"><input id="tags" name="tags" value="<?php echo $bookmark[tags]; ?>" /></td>
        </tr>
        <tr>
            <td class="label" valign="top"><label for="notes">Notes:</label></td>
            <td class="input"><div><textarea id="notes" name="notes"><?php echo $bookmark[notes]; ?></textarea></div></td>
        </tr>
        <tr>
            <td colspan="2"><sup>&#8224;</sup> Denotes required field</td>
        </tr>
        <tr>
            <td class="buttons" colspan="2">
		<input type="hidden" value="<?php echo $id ?>" id="id" name="bookmark" />
                <input type="button" value="Cancel" onclick="javascript:window.close();" />
                <input type="submit" value="Save Bookmark" style="font-weight: bold" />
            </td>
        </tr>
    </table>
</form>
<?php
	}
	else {
                $title = $_POST['name'];
                $url = $_POST['url'];
                $tags = $_POST['tags'];
		$notes = $_POST['notes'];

                $title = preg_replace('/</', '&lt;', $title);
                $url = preg_replace('/</', '&lt;', $url);
                $tags = preg_replace('/</', '&lt;', $tags);
		$notes = preg_replace('/</', '&lt;', $notes);
                $title = preg_replace('/>/', '&gt;', $title);
                $url = preg_replace('/>/', '&gt;', $url);
                $tags = preg_replace('/>/', '&gt;', $tags);
		$notes = preg_replace('/>/', '&gt;', $notes);

		$notes = preg_quote($notes);

		$bkhash = md5($url . $title);

		$ay_of_bookmarks[$bookmarkid] = array(title=>$title, url=>$url, tags=>$tags, notes=>$notes, id=>$bkhash);

                if ($ofp = fopen($file, "w")) {

			foreach ($ay_of_bookmarks as $outmark) {

                        	fwrite($ofp, "$outmark[title]\n");
                        	fwrite($ofp, "$outmark[url]\n");
                        	fwrite($ofp, "$outmark[tags]\n");
				fwrite($ofp, "$outmark[notes]\n");
			}

			fclose($ofp);

                        print "<p>Successfully editted bookmark</p>";
                        print "<p><a href=\"javascript:window.close();\">Close Window</a></p>";
                }
                else {
                        print "<p>Error couldn't open file</p>";
                        print "<p><a href=\"javascript:window.close();\">Close Window</a></p>";
                }


	}
?>
        </div>
    </body>
</html>
