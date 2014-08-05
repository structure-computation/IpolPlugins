class IpolTVDDemoItem extends TreeItem
    constructor: (name = 'ipol TVD')->
        super()
                
        @_name.set name
        
        @add_attr
            edited_by : 'CMLA'
            stamp: "img/TVD_demo.png"
            txt: "IPOL TVD"
            demo_app : "IpolTVDDemoItem"
            directory : "IPOL_TVD"
            video_link : undefined
            publication_link : undefined
            

    associated_application: ()->
        apps = new Lst
        apps.push new TreeAppApplication_IpolTVD
        return apps
    
    run_demo : (app_data)->
        app = new TreeAppApplication
        a = app.add_item_depending_selected_tree app_data, IpolTVDItem
        
            
    onclick_function: ()->
        window.location = "softpage.html#" +  @demo_app
