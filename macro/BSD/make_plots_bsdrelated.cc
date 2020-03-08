
void make_plots_bsdrelated()
{
  TString filepath = "./result/BSD/Accumlated_pot.root";
  TFile* fin = new TFile(filepath, "read");
  TH2D *bsd_plot = (TH2D*)fin->Get("bsd_accumlated_plot");
  TH2D *bm_plot = (TH2D*)fin->Get("bm_accumlated_plot");

  TString bsdplotname, bmplotname;
  TString delivered, recorded;
  Double_t eff;

  TCanvas *canvas = new TCanvas("canvas", "canvas", 1200, 800);
  canvas->SetGridx();
  canvas->SetGridy();
  canvas->cd();

  bsd_plot->Draw("");
  bm_plot->Draw("same");

  TLegend* legend = new TLegend(0.30, 0.70, 0.90, 0.90);
  delivered = "10.78+e20";
  recorded = "10.77+e20";
  //delivered = "2.644+e20";
  //recorded = "2.616+e20";
  eff = 10.77/10.78;
  bsdplotname.Form("Delivered P.O.T. (%s)", delivered.Data());
  bmplotname.Form("Recorded P.O.T. (%s)", recorded.Data());
  legend->AddEntry(bsd_plot,bsdplotname, "p");
  legend->AddEntry(bm_plot,bmplotname, "p");
  legend->Draw("same");
}
