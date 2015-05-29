<script type="text/javascript">
    evkey="";
    function loadMetric(){
        chartData.getCampaignPerformance(evkey,setGraph);
    }

    function setGraph(camp){
        var tiles = L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
                    maxZoom: 18,
                    attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors, Points &copy 2012 LINZ'
                }),
                latlng = L.latLng(37.8, -96);

        var map = L.map('map', {center: latlng, zoom: 4, layers: [tiles]});

        var markers = L.markerClusterGroup();

        var addressPoints = JSON.parse(camp);

        for (var i = 0; i < addressPoints.length; i++) {
            var a = addressPoints[i];
            var title = a[2];
            var marker = L.marker(new L.LatLng(a[0], a[1]), { title: title });
            marker.bindPopup(title);
            markers.addLayer(marker);
        }
        map.addLayer(markers);

    }

    function buttonClick(){
        evkey = document.getElementById("eventkey").value;
        if (evkey == ""){
            alert("Please provide an eventkey");
        }
        loadMetric();
    }


</script>