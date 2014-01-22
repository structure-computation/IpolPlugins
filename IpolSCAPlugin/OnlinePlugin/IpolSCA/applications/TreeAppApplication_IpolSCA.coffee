class TreeAppApplication_IpolSCA extends TreeAppApplication
    constructor: ->
        super()
        
        @name = 'Selective Contrast Adjustment'
        @powered_with = 'Ipol'
        @publication_link = 'http://www.ipol.im/pub/art/2013/41/'
        @tutorial_link = 'http://youtu.be/ayS5oDTgF7E'

        _ina = ( app ) =>
            app.data.focus.get() != app.selected_canvas_inst()?[ 0 ]?.cm.view_id
            
        @actions.push
            ico: "img/IpolSCA_bouton.png"
            siz: 1
            txt: "Ipol SCA"
            ina: _ina
            fun: ( evt, app ) =>
                app.undo_manager.snapshot()
                ipolSCA = @add_item_depending_selected_tree app.data, IpolSCAItem

