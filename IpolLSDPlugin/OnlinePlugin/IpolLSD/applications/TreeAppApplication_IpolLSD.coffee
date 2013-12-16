class TreeAppApplication_IpolLSD extends TreeAppApplication
    constructor: ->
        super()
        
        @name = 'Line Segment Detector'
        @powered_with = 'Ipol'
        @publication_link = 'http://www.ipol.im/pub/art/2012/gjmr-lsd/'

        _ina = ( app ) =>
            app.data.focus.get() != app.selected_canvas_inst()?[ 0 ]?.cm.view_id
            
        @actions.push
            ico: "img/IpolLSD_bouton.png"
            siz: 1
            txt: "Ipol LSD"
            ina: _ina
            fun: ( evt, app ) =>
                app.undo_manager.snapshot()
                ipolLsd = @add_item_depending_selected_tree app.data, IpolLSDItem

