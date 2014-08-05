class IpolSCADemoItem extends TreeItem
    constructor: (name = 'ipol ACE')->
        super()
                
        @_name.set name
        
        @add_attr
            edited_by : 'CMLA'
            stamp: "img/SCA_demo.png"
            txt: "IPOL SCA"
            demo_app : "IpolSCADemoItem"
            directory : "IPOL_SCA"
            video_link : undefined
            publication_link : undefined
            

    associated_application: ()->
        apps = new Lst
        apps.push new TreeAppApplication_IpolSCA
        return apps
    
    run_demo : (app_data)->
        app = new TreeAppApplication
        a = app.add_item_depending_selected_tree app_data, IpolSCAItem
        
            
    onclick_function: ()->
        window.location = "softpage.html#" +  @demo_app
