<?php
        # Name: Patrick Trinkle
        # Email: tri1@umbc.edu
        # Course: CMSC433
        # File: delete.php
        # Project: P3
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title>Delete Bookmark</title>
        <link rel="stylesheet" type="text/css" href="style.css" />
    </head>
    <body>
      <div class="form">
        <h1>Delete Bookmark</h1>
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
<p>Are you sure you want to delete the following?</p>
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
    <table>
        <tr>
            <td class="label">Name:</td>
            <td class="input"><?php echo $bookmark[title]; ?></td>
        </tr>
        <tr>
            <td class="label">URL:</td>
            <td class="input"><?php echo $bookmark[url]; ?></td>
        </tr>
        <tr>
            <td class="label">Tags:</td>
            <td class="input"><?php echo $bookmark[tags]; ?></td>
        </tr>
        <tr>
            <td class="label" valign="top">Notes:</td>
            <td class="input"><?php echo $bookmark[notes]; ?></td>
        </tr>
        <tr>
            <td class="buttons" colspan="2">
                <input type="hidden" name="bookmark" value="<?php echo $id; ?>" />
                <input type="button" value="Cancel" onclick="javascript:window.close();"/>
                <input type="submit" value="Delete Bookmark" style="font-weight: bold" />
            </td>
        </tr>
    </table>
</form>
<?php
        }
	// print the file out again but don't print that bookmark
        else {
                if ($ofp = fopen($file, "w")) {

                        foreach ($ay_of_bookmarks as $outmark) {

				if ( $id != $outmark[id] ) {
	                                fwrite($ofp, "$outmark[title]\n");
                                	fwrite($ofp, "$outmark[url]\n");
                                	fwrite($ofp, "$outmark[tags]\n");
					fwrite($ofp, "$outmark[notes]\n");
				}
                        }

                        fclose($ofp);

                        print "<p>Successfully deleted bookmark</p>";
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
