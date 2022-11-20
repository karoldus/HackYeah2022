<script>
  // core components
  import CardLineChart from "components/Cards/CardLineChart.svelte";
  import CardBarChart from "components/Cards/CardBarChart.svelte";
  import CardPageVisits from "components/Cards/CardPageVisits.svelte";
  import CardSocialTraffic from "components/Cards/CardSocialTraffic.svelte";
  export let location;
</script>

<div>
  <div class="flex flex-wrap">
    <div class="w-full xl:w-8/12 mb-12 xl:mb-0 px-4">
      <CardLineChart />
    </div>
    <div class="w-full xl:w-4/12 px-4">
      <CardBarChart />
    </div>
    <div class="w-full xl:w-12/12 px-4">
      <div
        class="relative flex flex-col min-w-0 break-words w-full mb-6 shadow-lg bg-white"
      >
        <div class="p-4 flex-auto">
          <div class="relative h-150-px text-center">
            <label>Time frame</label>
            <select name="Time Frame" id="">
              <option>Month</option>
            </select>
            <label>Compare to</label>
            <select name="Time Frame" id="">
              <option>Previous</option>
            </select>
            <label>Show</label>
            <select name="Show" id="">
              <option>Value</option>
            </select>
            <button
              class="bg-red-400 text-white active:bg-red-500 font-bold uppercase text-xs px-4 py-2 rounded shadow hover:shadow-md outline-none focus:outline-none mr-1 ease-linear transition-all duration-150"
              type="button"
            >
              <i class="fas fa-download" />
              Download CSV
            </button>
            <br />
            <br />
            <label>Set an alarm</label>
            <select name="Show" id="">
              <option>Above</option>
            </select>
            <input type="number" />
            <button
              class="bg-red-400 text-white active:bg-red-500 font-bold uppercase text-xs px-4 py-2 rounded shadow hover:shadow-md outline-none focus:outline-none mr-1 ease-linear transition-all duration-150"
              type="button"
            >
              <i class="fas fa-bell" />
              Set
            </button>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- <div class="flex flex-wrap mt-4">
    <div class="w-full xl:w-8/12 mb-12 xl:mb-0 px-4">
      <CardPageVisits />
    </div>
    <div class="w-full xl:w-4/12 px-4">
      <CardSocialTraffic />
    </div>
  </div> -->

  <!-- <button class="bg-green-500">Download CSV</button> -->
</div>
<br /><br />
