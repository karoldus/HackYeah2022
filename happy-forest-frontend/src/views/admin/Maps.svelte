<script>
  // core components
  import MapExample from "components/Maps/MapExample.svelte";
  export let location;
</script>

<div class="flex flex-wrap">
  <div class="w-full px-4">
    <div
      class="relative flex flex-col min-w-0 break-words bg-white w-full mb-6 shadow-lg rounded"
    >
      <MapExample />
    </div>
  </div>
  <button
    class="bg-red-400 text-white active:bg-red-500 font-bold uppercase text-xs px-4 py-2 rounded shadow hover:shadow-md outline-none focus:outline-none mr-1 ease-linear transition-all duration-150"
    type="button"
  >
    Download CSV
  </button>
</div>
<br /><br />
