<script>
  import { onMount } from "svelte";
  // library that creates chart objects in page
  import Chart from "chart.js";

  // init chart
  onMount(async () => {
    console.log(
      new Array(30).fill(0).map((_, i) => (Math.random() - 0.5) * 3 - i * 0.1)
    );
    var config = {
      type: "line",
      data: {
        labels: new Array(30).fill(0).map((_, i) => `${i}`),
        datasets: [
          {
            label: "This month",
            backgroundColor: "#1f6b2a", //"#4c51bf",
            borderColor: "#1f6b2a", //"#4c51bf",
            data: new Array(30)
              .fill(0)
              .map((_, i) => Math.random() - 0.5 - i * 0.02),
            fill: false,
          },
          {
            label: "Last month",
            fill: false,
            backgroundColor: "#6b351f",
            borderColor: "#6b351f",
            data: new Array(30)
              .fill(0)
              .map((_, i) => Math.random() - 0.5 + i * 0.05 - 1),
          },
        ],
      },
      options: {
        maintainAspectRatio: false,
        responsive: true,
        title: {
          display: false,
          text: "Value over time",
          fontColor: "black",
        },
        legend: {
          labels: {
            fontColor: "black",
          },
          align: "end",
          position: "bottom",
        },
        tooltips: {
          mode: "index",
          intersect: false,
        },
        hover: {
          mode: "nearest",
          intersect: true,
        },
        scales: {
          xAxes: [
            {
              ticks: {
                fontColor: "rgba(0,0,0,.7)",
              },
              display: true,
              scaleLabel: {
                display: false,
                labelString: "Month",
                fontColor: "white",
              },
              gridLines: {
                display: false,
                borderDash: [2],
                borderDashOffset: [2],
                color: "rgba(33, 37, 41, 0.3)",
                zeroLineColor: "rgba(33, 37, 41, 0.3)",
                // color: "rgba(33, 37, 41, 0.3)",
                // zeroLineColor: "rgba(0, 0, 0, 0)",
                zeroLineBorderDash: [2],
                zeroLineBorderDashOffset: [2],
              },
            },
          ],
          yAxes: [
            {
              ticks: {
                fontColor: "rgba(0,0,0,.7)",
              },
              display: true,
              scaleLabel: {
                display: false,
                labelString: "Value",
                fontColor: "white",
              },
              gridLines: {
                borderDash: [3],
                borderDashOffset: [3],
                drawBorder: false,
                color: "rgba(33, 37, 41, 0.2)",
                zeroLineColor: "rgba(33, 37, 41, 0.15)",
                // color: "rgba(255, 255, 255, 0.15)",
                // zeroLineColor: "rgba(33, 37, 41, 0)",
                zeroLineBorderDash: [2],
                zeroLineBorderDashOffset: [2],
              },
            },
          ],
        },
      },
    };
    var ctx = document.getElementById("line-chart").getContext("2d");
    window.myLine = new Chart(ctx, config);
  });
</script>

<div
  class="relative flex flex-col min-w-0 break-words w-full mb-6 shadow-lg bg-white"
>
  <div class="rounded-t mb-0 px-4 py-3 bg-transparent">
    <div class="flex flex-wrap items-center">
      <div class="relative w-full max-w-full flex-grow flex-1">
        <h6 class="uppercase text-blueGray-700 mb-1 text-xs font-semibold">
          Overview
        </h6>
        <h2 class="text-black text-xl font-semibold">Month</h2>
      </div>
    </div>
  </div>
  <div class="p-4 flex-auto">
    <!-- Chart -->
    <div class="relative h-350-px">
      <canvas id="line-chart" />
    </div>
  </div>
</div>
