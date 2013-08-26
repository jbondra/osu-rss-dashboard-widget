<div class="wrap">
<?php screen_icon( 'options-general' ); ?>
<h2>OSU RSS Dashboard Widget Options</h2>
<?php if ( isset( $_GET['updated'] ) ) : ?>
<div id="message" class="updated"><p><?php _e( 'Options saved.' ) ?></p></div>
<?php endif; ?>
<h3>Main Settings</h3>
<form method="post">
	<?php wp_nonce_field( 'osu_rss_dashboard_widget_options' ); ?>
	<table class="form-table">
	<tr valign="top">
		<th scope="row"><label for="feed_url"><?php _e( 'RSS Widget URL' ) ?></label></th>
		<td>
			<input class="regular-text" type="text" name="osu_rss_dashboard_widget_options[feed_url]" value="<?php echo $feed_url; ?>" />
			<br />
			Feed URL for U.OSU updates.
		</td>
	</tr>
	</table>
	
	<?php submit_button() ?>
</form>
</div>
