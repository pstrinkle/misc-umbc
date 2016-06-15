<?php
        # Name: Patrick Trinkle
        # Email: tri1@umbc.edu
        # Course: CMSC433
        # File: index.php
        # Project: P3
	# Required: index.php add.php delete.php edit.php style.css bookmarks.dat 
	# Data File: /afs/umbc.edu/users/t/r/tri1/pub/cs433/read-write/bookmarks.dat
	# Data File Format:
	#	Title
	#	URL
	#	key words seperated by spaces
	#	notes
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
    <head>
        <title>Bookmarks</title>
        <link rel="stylesheet" type="text/css" href="style.css" />
    </head>
    <body>
        <h1>Bookmarks</h1>
        <div class="bar">
            <div class="search">
              <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="get">
                <label for="search">Search:</label>
          	    <input type="text" id="search" name="search" value="" class="bordered" />
                <input type="submit" value="Go" />
              </form>
            </div>
            <a href="javascript:var tmp=window.open('http://userpages.umbc.edu/~tri1/cs433/web/p3/add.php','AddBookmark','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')">Add a Bookmark</a>
        </div>
<?php
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

			$ay_of_bookmarks[$ay_ctr] = array(title=>$name, url=>$url, tags=>$tags, notes=>$notes, id=>$hash);

			$ay_ctr++;
                }

                fclose($fp);
        }
        else {
                print "<p>Error couldn't open file</p>";
        }
?>
	<div class="contents">
<?php
	$query = $_GET['search'];

	if ( $query == '' ) {

		foreach ($ay_of_bookmarks as $bookmark) {
			$ay_tags = explode(" ", $bookmark[tags]);
?>
<div class="bookmark">
<a href="<?php echo $bookmark[url]; ?>" class="name"><?php echo $bookmark[title]; ?></a>
<?php if ($bookmark[tags] != "") { ?>
 - 
<?php } ?>
<?php 
			foreach ($ay_tags as $tag) {
?>
<a href="./?search=<?php echo $tag; ?>" class="tag"><?php echo $tag; ?></a>
<?php 			} ?>
<br />
<?php if ($bookmark[notes] != '') { ?> 
<span class="notes"><?php echo $bookmark[notes]; ?></span><br />
<?php } ?>
<span class="url"><?php echo $bookmark[url]; ?></span>
 - <a class="edit" href="javascript:var tmp=window.open('./edit.php?bookmark=<?php echo $bookmark[id]; ?>','EditBookmark','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')">Edit</a> 
<a class="edit" href="javascript:var tmp=window.open('./delete.php?bookmark=<?php echo $bookmark[id]; ?>','DeleteBookmark','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')">Delete</a>
</div>
<?php
		}
	}
	else {

		$query = preg_quote($query);

		$matches = 0;
		
		foreach ($ay_of_bookmarks as $bookmark) {

			if ( preg_match("/$query/i", $bookmark[tags]) ) {

				$matches = 1;
?>
<div class="bookmark">
<a href="<?php echo $bookmark[url]; ?>" class="name"><?php echo $bookmark[title]; ?></a>
 -
<?php
				$ay_tags = explode(" ", $bookmark[tags]);

                        	foreach ($ay_tags as $tag) {
?>
<a href="./?search=<?php echo $tag; ?>" class="tag"><?php echo $tag; ?></a>
<?php                   	} ?>
<br />
<?php if ($bookmark[notes] != '') { ?>
<span class="notes"><?php echo $bookmark[notes]; ?></span><br />
<?php } ?>
<span class="url"><?php echo $bookmark[url]; ?></span>
 - <a class="edit" href="javascript:var tmp=window.open('./edit.php?bookmark=<?php echo $bookmark[id]; ?>','EditBookmark','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')">Edit</a>
<a class="edit" href="javascript:var tmp=window.open('./delete.php?bookmark=<?php echo $bookmark[id]; ?>','DeleteBookmark','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')">Delete</a>
</div>
<?php
			}
		}
		if ( $matches == 0 ) {
			print "<p>No Bookmarks</p>";
		}
	}
?>

</div>

    <div class="bar" style="text-align: center">
        Bookmark pages more easily. Drag this bookmarklet to the Links area of your browser:
        <a href="javascript:var tmp=window.open('http://userpages.umbc.edu/~tri1/cs433/web/p3/add.php?name='+escape(document.title)+'&url='+escape(document.location),'AddBookmark','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')">Bookmark Page</a>
    </div>

    </body>
</html>
