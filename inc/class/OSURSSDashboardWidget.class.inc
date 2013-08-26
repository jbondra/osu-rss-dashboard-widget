<?php
/**
 * OSURSSDashboardWidget.class.inc
 * 	Defines the OSURSSDashboardWidget class 
 */

class OSURSSDashboardWidget {
	public function OSURSSDashboardWidget() {
		// actions	
		if ( is_admin() ) {
			add_action( 'admin_init', array( $this, 'admin_process_post' ) );
			add_action( 'network_admin_menu', array( $this, 'add_menus' ) );
			add_action( 'wp_dashboard_setup', array( $this, 'add_dashboard_widgets' ) );
		}
		add_action( 'muplugins_loaded', array( $this, 'create_options' ) );
		
	}
	
	public function create_options() {
		// create options if necessary
		$options = get_site_option( 'osu_rss_dashboard_widget_options' );
		
		if( $options === false ) {
			// options do not yet exist, create options
			
			$options = array(
				'feed_url' => 'https://u.osu.edu/feed/',
			);
			
			add_site_option( 'osu_rss_dashboard_widget_options', $options );
		}
	}
	
	public function add_menus() {
		add_submenu_page( 'settings.php', 'OSU Dashboard RSS Widget', 'OSU RSS Widget', 'manage_network_options', 'osu-dashboard-rss-widget', array( $this, 'options_page') );
	}
	
	public function options_page() {
		// check for appropriate access
		if ( ! current_user_can( 'manage_network_options' ) )
			wp_die( __( 'You do not have permission to access this page.' ) );
		
		$options = get_site_option( 'osu_rss_dashboard_widget_options' );
		$feed_url = $options['feed_url'];
		
		include( OSU_RSS_DASHBOARD_WIDGET_DIR . '/inc/view/options-page.view.inc' );
	}
	
	public function add_dashboard_widgets() {
		wp_add_dashboard_widget( 'osu_rss_dashboard_widget', 'U.OSU News', array( $this, 'rss_dashboard_widget' ) );
		
		// Globalize the metaboxes array, this holds all the widgets for wp-admin
		
		// move widget to side (http://codex.wordpress.org/Dashboard_Widgets_API#Advanced:_Adding_Widgets_onto_the_side)
		// Global the $wp_meta_boxes variable (this will allow us to alter the array).
		global $wp_meta_boxes;
		
		// Then we make a backup of your widget.
		$my_widget = $wp_meta_boxes['dashboard']['normal']['core']['osu_rss_dashboard_widget'];
		
		// We then unset that part of the array.
		unset($wp_meta_boxes['dashboard']['normal']['core']['osu_rss_dashboard_widget']);
		
		// Now we just add your widget back in.
		$wp_meta_boxes['dashboard']['side']['core']['osu_rss_dashboard_widget'] = $my_widget;
		
		// move widget to top (http://codex.wordpress.org/Dashboard_Widgets_API#Advanced:_Forcing_your_widget_to_the_top)
		
		// Get the regular dashboard widgets array 
		// (which has our new widget already but at the end)
	
		$normal_dashboard = $wp_meta_boxes['dashboard']['side']['core'];
		
		// Backup and delete our new dashboard widget from the end of the array
	
		$osu_rss_dashboard_widget_backup = array('osu_rss_dashboard_widget' => $normal_dashboard['osu_rss_dashboard_widget']);
		unset($normal_dashboard['osu_rss_dashboard_widget']);
	
		// Merge the two arrays together so our widget is at the beginning
	
		$sorted_dashboard = array_merge($osu_rss_dashboard_widget_backup, $normal_dashboard);
	
		// Save the sorted array back into the original metaboxes 
	
		$wp_meta_boxes['dashboard']['side']['core'] = $sorted_dashboard;
	}
	
	public function rss_dashboard_widget() {
		// look up feed
		$options = get_site_option( 'osu_rss_dashboard_widget_options' );
		$feed_url = $options['feed_url'];
		
		echo '<div class="rss-widget">';
		wp_widget_rss_output(
			array(
				'url' => $feed_url,
				'title' => 'U.OSU News',
				'items' => 4, //how many posts to show
				'show_summary' => 1,
				'show_author' => 0,
				'show_date' => 1
 			)
		);
		echo "</div>";
	}
	
	public function admin_process_post() {
		if ( isset( $_POST['osu_rss_dashboard_widget_options'] ) && current_user_can( 'manage_network_options' ) ) {
			check_admin_referer( 'osu_rss_dashboard_widget_options' );
			
			$new_options = array();
			$current_options = get_site_option( 'osu_rss_dashboard_widget_options' );
		
			if ( isset( $_POST['osu_rss_dashboard_widget_options']['feed_url'] ) ) {
				$new_options['feed_url'] = esc_url_raw( $_POST['osu_rss_dashboard_widget_options']['feed_url'] );
			}
			
			$options = array_merge( $current_options, $new_options );
			
			update_site_option( 'osu_rss_dashboard_widget_options', $options );
			
			$query_args = array(
				'updated' => 'true',
			);
		
			wp_redirect( add_query_arg( $query_args, network_admin_url( 'settings.php?page=osu-dashboard-rss-widget' ) ) );
			exit();
		}
	}
}
