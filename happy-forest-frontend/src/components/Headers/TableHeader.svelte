<script>
    // core components
    export let location;
    console.log(location.pathname);
</script>

<!-- Header -->
<div class="relative bg-green-700 md:pt-32 pb-32 pt-12">
    <div class="px-4 md:px-10 mx-auto w-full">
        <div class="text-center text-5xl text-white">
            {#if location.pathname === "/admin/tables"}
                <h1>Choose the type of data you want to work with</h1>
            {:else if location.pathname === "/admin/dashboard"}
                <h1>Temperature data for Sensor #0032</h1>
            {:else if location.pathname === "/admin/maps"}
                <h1>Choose sensor to examine</h1>
            {:else if location.pathname === "/admin/chooselocation"}
                <h1>Choose location</h1>
            {/if}
        </div>
    </div>
</div>
