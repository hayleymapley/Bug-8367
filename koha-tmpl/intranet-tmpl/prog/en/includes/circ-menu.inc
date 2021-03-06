[% USE Koha %]
[% USE KohaDates %]
[% IF ( patron.borrowernumber ) %]
<div class="patroninfo"><h5>[% INCLUDE 'patron-title.inc' %]</h5>

<input type="hidden" id="hiddenborrowernumber" value="[% patron.borrowernumber | html %]">
<input type="hidden" id="hiddenborrowername" value="[% patron.surname | html %] [% patron.firstname | html %]">
<input type="hidden" id="hiddenborrowercard" value="[% patron.cardnumber | html %]">

[% IF ( patronimages ) %]
    <div>
        <div class="patronimage-container">
            [% IF ( patron.image ) %]
                <img src="/cgi-bin/koha/members/patronimage.pl?borrowernumber=[% patron.borrowernumber | uri %]" class="patronimage" alt="[% patron.firstname | html %] [% patron.surname | html %] ([% patron.cardnumber | html %])" />
                <div class="patronimage-controls">
                    <div class="patronimage-control"><a data-borrowernumber="[% patron.borrowernumber | uri %]" class="btn btn-default edit-patronimage" title="Edit patron image" href="#"><i class="fa fa-pencil"></i> Edit</a></div>
                </div>
            [% ELSE %]
                <div class="patronimage empty"></div>
                <div class="patronimage-controls">
                    <div class="patronimage-control"><a data-borrowernumber="[% patron.borrowernumber | uri %]" class="btn btn-default edit-patronimage" title="Add patron image" href="#"><i class="fa fa-plus"></i> Add</a></div>
                </div>
            [% END %]
        </div>
    </div>
[% END %]

<ul class="patronbriefinfo">
    [% IF !(Koha.Preference('HidePersonalPatronDetailOnCirculation')) %]
        [% SWITCH Koha.Preference( 'AddressFormat' ) %]
            [% CASE 'de' %]
                [% INCLUDE 'member-display-address-style-de.inc' %]
            [% CASE # us %]
                [% INCLUDE 'member-display-address-style-us.inc' %]
        [% END %]

        [% IF ( patron.phone || patron.mobile || patron.phonepro ) %]<li class="patronphone">
        [% IF ( patron.phone ) %]
            <a href="tel:[% patron.phone | url %]">[% patron.phone | html %]</a>
        [% ELSE %]
            [% IF ( patron.mobile ) %]
                <a href="tel:[% patron.mobile | url %]">[% patron.mobile | html %]</a>
            [% ELSE %]
                [% IF ( patron.phonepro ) %]
                    <a href="tel:[% patron.phonepro | url %]">[% patron.phonepro | html %]</a>
                [% END %]
            [% END %]
        [% END %]</li>[% END %]
        [% IF ( patron.email ) %]
            <li class="email"> <a href="mailto:[% patron.email | url %]" title="[% patron.email | html %]">[% patron.email | html %]</a></li>
        [% ELSE %]
            [% IF ( patron.emailpro ) %]
                <li class="email"> <a href="mailto:[% patron.emailpro | url %]" title="[% patron.emailpro | html %]">[% patron.emailpro | html %]</a></li>
            [% END %]
        [% END %]

        [% UNLESS ( patron.address or patron.address2 ) %]
            <li><span class="empty" id="noaddressstored">No address stored.</span></li>
        [% END %]
        [% UNLESS ( patron.city ) %]
            <li><span class="empty" id="nocitystored">No city stored.</span></li>
        [% END %]
        [% UNLESS ( patron.phone or patron.mobile or patron.phonepro) %]
            <li> <span class="empty">No phone stored.</span></li>
        [% END %]
        [% UNLESS ( patron.email or patron.emailpro) %]
            <li> <span class="empty">No email stored.</span></li>
        [% END %]
    [% END %]

    [% IF Koha.Preference('ExtendedPatronAttributes') %]
        [% FOREACH extendedattribute IN patron.attributes %]
            [% IF ( extendedattribute.display_checkout ) %]
                <li class="patronattribute"><span class="patronattributelabel">[% extendedattribute.type_description | html %]</span> : [% IF ( extendedattribute.value_description ) %][% extendedattribute.value_description | html %][% ELSE %][% extendedattribute.attribute | html %][% END %]</li>
            [% END %]
        [% END %]
    [% END %]
    <li class="patroncategory">Category: [% patron.category.description | html %] ([% patron.categorycode | html %])</li>
    <li class="patronlibrary">Home library: [% Branches.GetName( patron.branchcode ) | html %]</li>
    <li class="patronborrowernumber">Borrowernumber: [% patron.borrowernumber | html %]</li>
    <li><span class="patronupdatedon">Updated on [% patron.updated_on | $KohaDates with_hours => 1 %]</span></li>
  </ul></div>
<div id="menu">
<ul>
    [% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
        [% IF ( circview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/circ/circulation.pl?borrowernumber=[% patron.borrowernumber | uri %]">Check out</a></li>
        [% IF Koha.Preference('BatchCheckouts') && Koha.Preference('BatchCheckoutsValidCategories').split('\|').grep('^' _ patron.categorycode _ '$').size > 0 %]
          [% IF ( batch_checkout_view ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/circ/circulation.pl?borrowernumber=[% patron.borrowernumber | uri %]&amp;batch=1">Batch check out</a></li>
        [% END %]
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers %]
        [% IF ( detailview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/moremember.pl?borrowernumber=[% patron.borrowernumber | uri %]">Details</a></li>
    [% END %]
    [% IF ( CAN_user_updatecharges ) %]
        [% IF ( finesview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/pay.pl?borrowernumber=[% patron.borrowernumber | uri %]">Accounting</a></li>
    [% END %]
    [% IF ( CAN_user_circulate_circulate_remaining_permissions  )  %]
        [% IF Koha.Preference("RoutingSerials") %][% IF ( routinglistview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/routing-lists.pl?borrowernumber=[% patron.borrowernumber | uri %]">Routing lists</a></li>[% END %]
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers %]
        [% IF ( intranetreadinghistory ) %]
            [% IF ( readingrecordview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/readingrec.pl?borrowernumber=[% patron.borrowernumber | uri %]">Circulation history</a></li>
        [% END %]
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers %]
        [% IF ( intranetreadinghistory ) %]
            [% IF ( holdshistoryview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/holdshistory.pl?borrowernumber=[% patron.borrowernumber | uri %]">Holds history</a></li>
        [% END %]
    [% END %]
    [% IF ( CAN_user_tools_view_system_logs ) %]
        [% IF ( logview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/tools/viewlog.pl?do_it=1&amp;modules=MEMBERS&amp;modules=CIRCULATION&amp;object=[% patron.borrowernumber | uri %]&amp;src=circ">Modification log</a></li>
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers %]
    [% IF ( sentnotices ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/notices.pl?borrowernumber=[% patron.borrowernumber | uri %]">Notices</a></li>
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers %]
        [% IF (  statisticsview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/statistics.pl?borrowernumber=[% patron.borrowernumber | uri %]">Statistics</a></li>
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers %]
        [% IF ( EnableBorrowerFiles ) %]
            [% IF ( borrower_files ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/files.pl?borrowernumber=[% patron.borrowernumber | uri %]">Files</a></li>
        [% END %]
    [% END %]

    [% IF CAN_user_acquisition_suggestions_manage %]
        [% IF ( suggestionsview ) %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/purchase-suggestions.pl?borrowernumber=[% patron.borrowernumber | uri %]">Purchase suggestions</a></li>
    [% END %]
    [% IF CAN_user_borrowers_edit_borrowers && useDischarge %]
        [% IF dischargeview %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/discharge.pl?borrowernumber=[% patron.borrowernumber | uri %]">Discharges</a></li>
    [% END %]
    [% IF Koha.Preference('HouseboundModule') %]
        [% IF houseboundview %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/housebound.pl?borrowernumber=[% patron.borrowernumber | uri %]">Housebound</a></li>
    [% END %]
    [% IF Koha.Preference('ILLModule') && CAN_user_ill %]
        [% IF illview %]<li class="active">[% ELSE %]<li>[% END %]<a href="/cgi-bin/koha/members/ill-requests.pl?borrowernumber=[% patron.borrowernumber | uri %]">ILL requests history</a></li>
    [% END %]
</ul></div>

<!-- Modal -->
<div class="modal" id="patronImageEdit" tabindex="-1" role="dialog" aria-labelledby="patronImageEditLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="closebtn" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="patronImageEditLabel">Modal title</h4>
            </div>
            <div class="modal-body">
                <img src="[% interface | html %]/[% theme | html %]/img/spinner-small.gif" alt="" />
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
            </div>
        </div>
    </div>
</div>

[% END %]
