<?php
/**
 * osu-rss-dashboard-widget.php
 * 	sets up OSU RSS Dashboard Widget Plugin
 */

// constants
define( 'OSU_RSS_DASHBOARD_WIDGET_BASENAME', basename( dirname(__FILE__) ) );
define( 'OSU_RSS_DASHBOARD_WIDGET_DIR', dirname(__FILE__) );
define( 'OSU_RSS_DASHBOARD_WIDGET_URL', WPMU_PLUGIN_URL . '/' . OSU_RSS_DASHBOARD_WIDGET_BASENAME );

// activate plugin
if ( !class_exists('OSURSSDashboardWidget') ) {
	require( 'inc/class/OSURSSDashboardWidget.class.inc' );
}
$osu_rss_dashboard_widget = new OSURSSDashboardWidget();
