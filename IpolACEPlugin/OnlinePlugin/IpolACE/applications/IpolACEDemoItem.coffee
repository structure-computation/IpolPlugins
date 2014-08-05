class IpolACEDemoItem extends TreeItem
    constructor: (name = 'ipol ACE')->
        super()
                
        @_name.set name
        
        @add_attr
            edited_by : 'CMLA'
            stamp: "img/ACE_demo.png"
            txt: "IPOL ACE"
            demo_app : "IpolACEDemoItem"
            directory : "IPOL_ACE"
            video_link : '<iframe width="853" height="480" src="//www.youtube.com/embed/TXmLqJS0nvE?rel=0" frameborder="0" allowfullscreen></iframe>'
            publication_link : '<iframe width="1100" height="1550" frameborder="0" style="border:0" id="pdfviewer" src="http://docs.google.com/viewer?url=http://www.ipol.im/pub/art/2012/gjmr-lsd//article_lr.pdf&amp;embedded=true">Preview not available in your browser.</iframe>'
            

    associated_application: ()->
        apps = new Lst
        apps.push new TreeAppApplication_IpolACE
        return apps
    
    run_demo : (app_data)->
        app = new TreeAppApplication
        a = app.add_item_depending_selected_tree app_data, IpolACEItem
        
            
    onclick_function: ()->
        window.location = "softpage.html#" +  @demo_app
