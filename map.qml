
import QtPositioning 5.6
import QtQuick 2.7
import QtLocation 5.6

Rectangle
{
    id:window
    property double latitude:54.5072
    property double longitude:0.1276
    property Component locationmarker: locmaker
    Plugin
    {
        id:googlemapview
        name:"osm"
    }
    Map
    {
        id:mapview
        anchors.fill: parent
        plugin: googlemapview
        center: QtPositioning.coordinate(latitude,longitude)
        zoomLevel:  10
    }
    function setCenterPosition(lati,longi)
    {
        mapview.pan(lati,longi)
        latitude=lati
        longitude=longi
    }
}
