<script>
  import { onMount } from "svelte";
  import { navigate } from "svelte-routing";

  // init google maps
  onMount(async () => {
    let google = window.google;
    let map = document.getElementById("map-canvas");
    let lat = map.getAttribute("data-lat");
    let lng = map.getAttribute("data-lng");

    const myLatlng = new google.maps.LatLng(lat, lng);
    const mapOptions = {
      zoom: 12,
      scrollwheel: false,
      center: myLatlng,
      mapTypeId: google.maps.MapTypeId.ROADMAP,
      styles: [
        {
          featureType: "administrative",
          elementType: "labels.text.fill",
          stylers: [{ color: "#1f6b2a" }],
        },
        {
          featureType: "landscape",
          elementType: "all",
          stylers: [{ color: "black" }],
        },
        {
          featureType: "poi",
          elementType: "all",
          stylers: [{ visibility: "off" }],
        },
        {
          featureType: "road",
          elementType: "all",
          stylers: [{ color: "black" }],
        },
        {
          featureType: "road.highway",
          elementType: "all",
          stylers: [{ visibility: "simplified" }],
        },
        {
          featureType: "road.arterial",
          elementType: "labels.icon",
          stylers: [{ visibility: "off" }],
        },
        {
          featureType: "transit",
          elementType: "all",
          stylers: [{ visibility: "off" }],
        },
        {
          featureType: "water",
          elementType: "all",
          stylers: [{ color: "#1f606b" }, { visibility: "on" }],
        },
      ],
    };

    map = new google.maps.Map(map, mapOptions);

    // const marker = new google.maps.Marker({
    //   position: myLatlng,
    //   map: map,
    //   animation: google.maps.Animation.DROP,
    //   title: "Hello World!",
    // });
    const locations = [
      [52.32925, 20.723667],
      [52.33925, 20.723667],
      [52.33925, 20.703667],
      [52.33925, 20.603667],
      [52.35925, 20.603667],
      [52.39925, 20.653667],
      [52.29925, 20.673667],
      [52.27925, 20.703667],
    ];
    const positions = locations.map(
      ([lat, lng]) => new google.maps.LatLng(lat, lng)
    );
    const markers = positions.map(
      (position) =>
        new google.maps.Marker({
          position,
          map,
          // label: { text: "dupa", fontSize: "20px", fontWeight: "bold" },
        })
    );
    for (let marker of markers) {
      const infowindow = new google.maps.InfoWindow({
        content: (Math.floor(Math.random() * 200 - 1) / 100).toString() + "°C",
      });
      infowindow.open(map, marker);
      google.maps.event.addListener(marker, "click", () => {
        navigate("/admin/dashboard");
      });
    }

    // const marker = new google.maps.Marker({
    //   position: new google.maps.LatLng(52.32925, 20.723667),
    //   map: map,
    //   animation: google.maps.Animation.DROP,
    //   title: "Hello World!",
    // });

    // const marker2 = new google.maps.Marker({
    //   position: new google.maps.LatLng(52.33925, 20.723667),
    //   map: map,
    //   animation: google.maps.Animation.DROP,
    // });

    const contentString =
      '<div class="info-window-content"><h2>Notus Svelte</h2>' +
      "<p>A beautiful UI Kit and Admin for Tailwind CSS. It is Free and Open Source.</p></div>";

    const infowindow = new google.maps.InfoWindow({
      content: contentString,
    });

    // google.maps.event.addListener(marker, "click", function () {
    //   infowindow.open(map, marker);
    // });
  });
</script>

<div
  id="map-canvas"
  class="relative w-full rounded h-600-px"
  data-lat="52.329250"
  data-lng="20.723667"
/>
